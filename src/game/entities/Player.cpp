/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include <game/components/PlayerComponent.hpp>
#include <engine/components/IrrlichtComponent.hpp>
#include <engine/components/TagComponent.hpp>
#include <game/components/MasterComponent.hpp>
#include <engine/components/PhysicsComponent.hpp>
#include <engine/components/AnimationComponent.hpp>
#include <engine/components/HoldComponent.hpp>
#include <game/events/Vector.hpp>
#include <engine/systems/PhysicsSystem.hpp>
#include <game/systems/PlayerSystem.hpp>
#include <engine/components/ItemComponent.hpp>
#include <game/components/WeaponComponent.hpp>
#include "Player.hpp"

worms::EntityModeller::EntityModeller(engine::Game& game, engine::Scene& scene) : _game(game), _scene(scene)
{}

worms::Player::Player(engine::Game& game, engine::Scene& scene) : EntityModeller(game, scene)
{}

void
worms::Player::operator()(engine::Entity const& entity)
{
	entity.set<PlayerComponent>();
	entity.set<engine::IrrlichtComponent>(&_game, "obj/silinoid.ms3d", "texture/player_jason.png");
	entity.set<engine::TagComponent>(std::string("player"));
	_scene.getEntities().each<MasterComponent>([&](auto const& e, auto& m) {
		m.players.push_back(entity.getId());
	});

	auto& physicsComponent = entity.set<engine::PhysicsComponent>();
	auto& transformComponent = entity.set<engine::TransformComponent>();
	auto& animationComponent = entity.set<engine::AnimationComponent>("idle", 60);

	engine::AnimationBoundaries idle(0, 80);
	engine::AnimationBoundaries run(80, 40);
	engine::AnimationBoundaries jump(120, 35);
	engine::AnimationBoundaries inAir(155, 25);

	animationComponent.states.emplace("idle", idle);
	animationComponent.states.emplace("run", run);
	animationComponent.states.emplace("jump", jump);
	animationComponent.states.emplace("inAir", inAir);

	irr::s32 holdHeavyOffset = 290;
	animationComponent.states.emplace("idleHoldHeavy", idle + holdHeavyOffset);
	animationComponent.states.emplace("runHoldHeavy", run + holdHeavyOffset);
	animationComponent.states.emplace("jumpHoldHeavy", jump + holdHeavyOffset);
	animationComponent.states.emplace("inAirHoldHeavy", inAir + holdHeavyOffset);

	transformComponent.scale = {0.5f, 0.5f, 0.5f};
	transformComponent.position = {0.f, 25.f, 0.f};

	auto& hitboxComponent = entity.set<engine::HitboxComponent>("(-1 0, -1 4, 1 4, 1 0)");
	hitboxComponent.rebound = 0.1f;

	auto& hc = entity.set<engine::HoldComponent>();

	// give pickaxe
	auto pickaxe = _scene.spawnEntity("pickaxe");
	auto& h = pickaxe.get<engine::HitboxComponent>();
	auto& t = pickaxe.get<engine::TransformComponent>();
	engine::GeometryHelper::transformHitbox(h, t);
	auto item = entity.attach(pickaxe);
	hc.items[++hc.current] = item;
	hc.count += 1;

	_scene.registerEvent<std::string>("player.move", entity.getId(), [&](std::string const& move) {
		auto _move = (Vector2f)move;
		physicsComponent.move = _move;

		if (_move.x > 0)
			transformComponent.direction = true;
		else if (_move.x < 0)
			transformComponent.direction = false;
		return 0;
	});

	_scene.registerEvent<std::string>("player.jump", entity.getId(), [entity, this, &physicsComponent, &animationComponent, &hc](std::string const& jump) {
		if (engine::PhysicsSystem::isGrounded(_scene.getEntities(), entity)) {
			physicsComponent.velocity += (Vector2f) jump;
			animationComponent.currentState = PlayerSystem::getState("jump", hc);
			animationComponent.playOnce = true;
			animationComponent.nextState = PlayerSystem::getState("inAir", hc);
		}

		return 0;
	});

	_scene.registerEvent<std::string>("player.pick", entity.getId(), [entity, &hc](std::string const& s) {
		if (hc.hasReachableEntity) {
			if (hc.items.size() == hc.count) {
				engine::Entity& item = hc.items[hc.current];
				item.detach();

				auto item2 = entity.attach(hc.reachableEntity);
				hc.items[hc.current] = item2;
			} else {
				if (hc.current >= 0) {
					hc.items[hc.current].disable();
				}
				auto item = entity.attach(hc.reachableEntity);
				hc.items[++hc.current] = item;
				hc.count += 1;
			}
			hc.hasReachableEntity = false;
		}
		return 0;
	});

	_scene.registerEvent<std::string>("player.use", entity.getId(), [entity, &hc](std::string const& s) {
		engine::Entity& item = hc.items[hc.current];
		if (hc.current >= 0) {
			if (item.has<engine::ItemComponent>()) {
				item.get<engine::ItemComponent>().use();
			}
		}
		return 0;
	});

	_scene.registerEvent<std::string>("player.aim", entity.getId(), [entity, &hc](std::string const& move) {
		if (hc.current >= 0) {
			engine::Entity& item = hc.items[hc.current];
			if (item.has<engine::ItemComponent>() && item.has<WeaponComponent>()) {
				auto& weapon = item.get<WeaponComponent>();
				if (weapon.hasAim)
					weapon.aimPosition += (Vector2f)move;
			}
		}
		return 0;
	});

	_scene.registerEvent<std::string>("player.play", entity.getId(), [this, entity](std::string const&) {
		_game.eventsHandler.subscribe<Vector2f>(_scene, engine::KeyCode::KEY_KEY_Q, "player.move", entity.getId(), Vector2f(-10.f, 0.f), engine::EVT_SYNCED | engine::EVT_OVERRIDE);
		_game.eventsHandler.subscribe<Vector2f>(_scene, engine::KeyCode::KEY_KEY_Q, "player.move", entity.getId(), Vector2f(0.f, 0.f), engine::EVT_SYNCED | engine::EVT_RELEASE);
		_game.eventsHandler.subscribe<Vector2f>(_scene, engine::KeyCode::KEY_KEY_D, "player.move", entity.getId(), Vector2f(10.f, 0.f), engine::EVT_SYNCED | engine::EVT_OVERRIDE);
		_game.eventsHandler.subscribe<Vector2f>(_scene, engine::KeyCode::KEY_KEY_D, "player.move", entity.getId(), Vector2f(0.f, 0.f), engine::EVT_SYNCED | engine::EVT_RELEASE);
		_game.eventsHandler.subscribe<Vector2f>(_scene, engine::KeyCode::KEY_SPACE, "player.jump", entity.getId(), Vector2f(0.f, 70.f), engine::EVT_SYNCED | engine::EVT_OVERRIDE);
		_game.eventsHandler.subscribe<std::string>(_scene, engine::KeyCode::KEY_KEY_R, "player.pick", entity.getId(), "0", engine::EVT_SYNCED | engine::EVT_OVERRIDE);
		_game.eventsHandler.subscribe<std::string>(_scene, engine::KeyCode::KEY_KEY_S, "player.use", entity.getId(), "0", engine::EVT_SYNCED | engine::EVT_OVERRIDE);
		_game.eventsHandler.subscribe<Vector2f>(_scene, engine::KeyCode::KEY_UP, "player.aim", entity.getId(), Vector2f(0.f, 1.f), engine::EVT_SYNCED | engine::EVT_OVERRIDE);
		_game.eventsHandler.subscribe<Vector2f>(_scene, engine::KeyCode::KEY_RIGHT, "player.aim", entity.getId(), Vector2f(1.f, 0.f), engine::EVT_SYNCED | engine::EVT_OVERRIDE);
		_game.eventsHandler.subscribe<Vector2f>(_scene, engine::KeyCode::KEY_DOWN, "player.aim", entity.getId(), Vector2f(0.f, -1.f), engine::EVT_SYNCED | engine::EVT_OVERRIDE);
		_game.eventsHandler.subscribe<Vector2f>(_scene, engine::KeyCode::KEY_LEFT, "player.aim", entity.getId(), Vector2f(-1.f, 0.f), engine::EVT_SYNCED | engine::EVT_OVERRIDE);

		return 0;
	});
}
