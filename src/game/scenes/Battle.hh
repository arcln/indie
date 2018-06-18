//
//  BattleSceneModel.hpp
//  engine
//
//  Created by Arthur Chaloin on 14/05/2018.
//

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <game/map/Map.hpp>
#include <game/entities/Player.hpp>
#include "engine/helpers/GeometryHelper.hpp"
#include "engine/core/Game.hpp"
#include "engine/systems/PhysicsSystem.hpp"
#include "engine/components/LightComponent.hpp"
#include "engine/components/IrrlichtComponent.hpp"
#include "engine/components/HitboxComponent.hpp"
#include "engine/components/TransformComponent.hpp"
#include "engine/components/AnimationComponent.hpp"
#include "engine/components/TagComponent.hpp"
#include "engine/components/CameraComponent.hpp"
#include "engine/components/PhysicsComponent.hpp"
#include "engine/components/ItemComponent.hpp"
#include "engine/components/HoldComponent.hpp"
#include "engine/components/ParticlesComponent.hpp"
#include "engine/components/TimeoutComponent.hpp"
#include "engine/components/TextComponent.hpp"
#include "game/components/MasterComponent.hpp"
#include "game/components/PlayerComponent.hpp"
#include "game/components/WeaponComponent.hpp"
#include "game/events/Vector.hpp"

namespace worms { namespace scene {

	static const auto battle = [](engine::Game& game, engine::Scene& scene) {

		scene.registerEntityModel("master", [&scene](engine::Entity const& entity) {
			entity.set<MasterComponent>().currentPlayer = 0;
			entity.set<engine::TagComponent>("master");
			entity.set<engine::TimeoutComponent>(8.f, [&scene]() {
				scene.triggerEvent<std::string>("master.changePlayer");
			}, true);
		});

		scene.registerEntityModel("camera", [&](engine::Entity const& entity) {
			entity.set<engine::TransformComponent>();

			auto& cameraComponent = entity.set<engine::CameraComponent>(game.device());

			scene.registerEvent<Vector3f>("camera.goto", entity.getId(), [&](auto const& position) {
				cameraComponent.node->setPosition(position);
				return 0;
			});

			scene.registerEvent<Vector3f>("camera.lookat", entity.getId(), [&](auto const& position) {
				cameraComponent.node->setTarget(position);
				return 0;
			});

			scene.registerEvent<Vector3f>("camera.move", entity.getId(), [&](auto const& offset) {
				cameraComponent.node->setPosition(cameraComponent.node->getPosition() + offset);
				cameraComponent.node->setTarget(cameraComponent.node->getTarget() + offset);
				return 0;
			});
		});

		scene.registerEntityModel("explosion", [&](engine::Entity const& entity) {
			auto& transformComponent = entity.set<engine::TransformComponent>();
			auto& particlesComponent = entity.set<engine::ParticlesComponent>(game.device(), 1, 2);

			entity.set<engine::TimeoutComponent>(.08f, [&particlesComponent]() -> void {
				particlesComponent.node->setEmitter(nullptr);
			});

			entity.set<engine::TimeoutComponent>(1.f, [entity]() -> void {
				entity.kill();
			});

			particlesComponent.node->setMaterialTexture(0, engine::ResourceManager<engine::Texture*>::instance().get("texture/explosion_particle.jpg"));
			particlesComponent.node->getEmitter()->setMinStartSize(irr::core::dimension2df(1.f, 1.f));
			particlesComponent.node->getEmitter()->setMaxStartSize(irr::core::dimension2df(3.f, 3.f));
			particlesComponent.node->getEmitter()->setMinStartColor(irr::video::SColor(0, 255, 200, 190));
			particlesComponent.node->getEmitter()->setMaxStartColor(irr::video::SColor(0, 255, 255, 255));
		});

		scene.registerEntityModel("player", Player(game, scene));

		scene.registerEntityModel("light", [&](engine::Entity const& entity) {
			entity.set<engine::LightComponent>(game.device(), irr::core::vector3df(0, 500, 50), irr::video::SColorf(0.0f, 0.0f, 0.0f), 1000
											   );
		});

		scene.registerEntityModel("pickaxe", [&](engine::Entity const& entity) {
			entity.set<engine::TagComponent>(std::string("pickaxe"));

			auto& wc = entity.set<WeaponComponent>();
			wc.hasAim = true;

			entity.set<engine::IrrlichtComponent>(&game, "obj/pickaxe.obj");
			entity.set<engine::PhysicsComponent>();

			entity.set<engine::HitboxComponent>("(-8 -3, -8 3, 6 3, 6 -3)");

			auto& transformComponent = entity.set<engine::TransformComponent>();
			transformComponent.position = {5.f, 10.f, 0.f};
			transformComponent.scale = {0.15f, 0.15f, 0.15f};
			transformComponent.offset = {0.f, -3.2f, 0.f};
			transformComponent.rotation = {0.f, 180.f, 0.f};

			auto& ic = entity.set<engine::ItemComponent>();
			ic.use = [&]() {
				auto p = wc.aimPosition;
				p.normalize();
				Wornite::Map::tryDestroyMap(scene, transformComponent.position.X + p.X, transformComponent.position.Y + p.Y, 1.5f, false);
			};
            ic.offset = {1.3f, 1.f, 0.f};
		});

		scene.registerEntityModel("sword", [&](engine::Entity const& entity) {
			entity.set<engine::TagComponent>(std::string("sword"));
			entity.set<engine::IrrlichtComponent>(&game, "obj/sword.obj");
			entity.set<engine::PhysicsComponent>();

			auto& transformComponent = entity.set<engine::TransformComponent>();
			transformComponent.position = {10.f, 10.f, 0.f};
			transformComponent.scale = {0.25f, 0.25f, 0.25f};
			transformComponent.offset = {0.f, -5.8f, 0.f};
			transformComponent.offsetRotation = {0.f, -90.f, 0.f};

			auto& hitboxComponent = entity.set<engine::HitboxComponent>("(-6 -1.5, -6 1.5, 6 1.5, 6 -1.5)");
			hitboxComponent.rebound = 0.2;

			auto& ic = entity.set<engine::ItemComponent>([]() {
				std::cout << "use item\n";
			});
			ic.offset = {1.65f, 1.f, 0.f};
		});

        scene.registerEntityModel("rpg.bullet", [&](engine::Entity const& entity) {
			entity.set<engine::TagComponent>(std::string("projectile"));
			entity.set<engine::IrrlichtComponent>(&game, "obj/missile.obj", "texture/missile.png");
			entity.set<engine::PhysicsComponent>();

			auto& transformComponent = entity.set<engine::TransformComponent>();
			transformComponent.scale = {0.25f, 0.25f, 0.25f};
			auto& hitboxComponent = entity.set<engine::HitboxComponent>("(-1 -1, -1 1, 1 1, 1 -1)");
			hitboxComponent.onCollide = [entity, &scene, &transformComponent](engine::Entity const& collideWith) -> void {
				entity.set<engine::TimeoutComponent>(0.0001f, [entity, &scene, &transformComponent]() -> void {
					Wornite::Map::tryDestroyMap(scene, transformComponent.position.X, transformComponent.position.Y, 2.f);
					entity.kill();
				});
				auto& explosionTransform = scene.spawnEntity("explosion").get<engine::TransformComponent>();
				explosionTransform.position = transformComponent.position;
			};
		});

		scene.registerEntityModel("rpg", [&](engine::Entity const& entity) {
			entity.set<engine::TagComponent>(std::string("rpg"));
			entity.set<engine::IrrlichtComponent>(&game, "obj/rpg.obj", "texture/rpg.png");
			entity.set<engine::PhysicsComponent>();

			auto& transform = entity.set<engine::TransformComponent>();
			transform.position = {10.f, 10.f, 0.f};
			transform.scale = {0.4f, 0.4f, 0.4f};
			transform.offsetRotation = {0.f, -90.f, 0.f};

			auto& hitboxComponent = entity.set<engine::HitboxComponent>("(-1 -1, -1 1, 1 1, 1 -1)");
			hitboxComponent.rebound = 0.2;

			auto& weapon = entity.set<WeaponComponent>();
			weapon.hasAim = true;

			auto& item = entity.set<engine::ItemComponent>([&scene, &transform, &weapon]() {
				auto bullet = scene.spawnEntity("rpg.bullet");
				auto& bulletTransform = bullet.get<engine::TransformComponent>();
				auto& bulletPhysics = bullet.get<engine::PhysicsComponent>();

				bulletPhysics.velocity = weapon.aimPosition;
				bulletPhysics.velocity = bulletPhysics.velocity.normalize() * 100.f;
				bulletTransform.position = transform.position;
				bulletTransform.position.X += bulletPhysics.velocity.X / 200;
				bulletTransform.position.Y += bulletPhysics.velocity.Y / 200;
			});
			item.heavy = true;
			item.offset = {0.7f, 1.f, 0.f};
		});

		scene.registerEvent<std::string>("master.changePlayer", 0, [&scene](std::string const& player) {
			scene.getEntities().each<MasterComponent>([&scene, &player](engine::Entity const& e, auto& m) {
				scene.triggerSyncedEvent("player.move", m.players[m.currentPlayer], Vector2f(0.f, 0.f).serialize());

				try {
					m.currentPlayer = std::stoi(player);
				} catch (std::exception& e) {
					++m.currentPlayer;
					if (m.currentPlayer >= static_cast<int>(m.players.size())) {
						m.currentPlayer = 0;
					}
				}
				scene.triggerSyncedEvent("player.play", m.players[m.currentPlayer], "");
			});

			return 0;
		});

		scene.registerEvent<std::string>("master.win", 0, [&](auto const&) {
			game.replaceScene("gameOver");
			return 0;
		});

		scene.registerEntityModel("timer", [&](engine::Entity const& entity) {
			entity.set<engine::TagComponent>("timer");
			static irr::s32 id = 0;
			auto& staticTextComponent = entity.set<engine::TextComponent>(game.device(), L"30", irr::core::rect<irr::s32>(10, 10, 300, 300), false, false, nullptr, id, false);
			staticTextComponent.node->setWordWrap(false);
			staticTextComponent.node->setOverrideFont(game.device()->getGUIEnvironment()->getFont(L"../assets/font/PTSans48/PTSans48.xml"));
		});

		scene.registerEntityModel("background", [&](engine::Entity const& entity) {
			auto& i = entity.set<engine::IrrlichtComponent>(&game, "obj/spaceBackground.obj");
			auto& t = entity.set<engine::TransformComponent>();

			t.scale *= 550;
			t.scale.Y *= 1200.f / 1920.f;
			t.rotation.X = 10;
			t.position.Z = 200;
		});

		scene.registerEvent<std::string>("player.spawn", 0, [&](std::string const& pos) {
			scene.spawnEntity("rpg");
			scene.spawnEntity("player", [&](engine::Entity const& entity) {
				entity.get<engine::TransformComponent>().position = (Vector3f) pos;
			});
			return 0;
		});

		scene.registerEntityModel("map", [&](engine::Entity const& entity) {
			Wornite::Map().genMap(game, scene).getSeed();

			scene.registerEvent<std::string>("map.hitbox.display", 0, [&](std::string const& move) {
				static bool DebugMode = true;
				engine::Entities entities = scene.getEntities();
				entities.withTag("map", [&](engine::Entity const& chunk) {
					entities.eachChilds(chunk.getId(), [&](engine::Entity const &child) {
						auto& h = child.get<engine::HitboxComponent>();

					});
				});
				DebugMode = !DebugMode;
				return 0;
			});

			return 0;
		});

		game.eventsHandler.subscribe<std::string>(scene, engine::KeyCode::KEY_KEY_E, "player.spawn", 0, std::to_string(1));
		game.eventsHandler.subscribe<std::string>(scene, engine::KeyCode::KEY_KEY_P, "master.changePlayer", 0, std::to_string(1));
		game.eventsHandler.subscribe<std::string>(scene, engine::KeyCode::KEY_KEY_O, "master.changePlayer", 0, std::to_string(0));
		game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_H, "map.hitbox.display", 0, Vector2f(0.f, 0.f), engine::EVT_SYNCED);

		scene.spawnEntity("master");
		scene.spawnEntity("camera");
		scene.spawnEntity("map");
		scene.spawnEntity("light");
		scene.spawnEntity("sword");
		scene.spawnEntity("pickaxe");
		scene.spawnEntity("rpg");
		scene.spawnEntity("sword");
		scene.spawnEntity("background");
		scene.spawnEntity("timer");

		for (auto i = 0; i < 2; ++i) {
			scene.triggerEvent<std::string>("player.spawn", 0, Vector3f(10.f * i - 5.f, 25.f, 0.f).serialize());
		}

		scene.triggerEvent<std::string>("master.changePlayer", 0, "0");
	};
}}
