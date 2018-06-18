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
#include <irrlicht/irrlicht.h>
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

		scene.registerEntityModel("player", [&](engine::Entity const& entity) {
			entity.set<PlayerComponent>();
			entity.set<engine::IrrlichtComponent>(&game, "obj/silinoid.ms3d", "texture/player_jason.png");
			entity.set<engine::TagComponent>(std::string("player"));
			scene.getEntities().each<MasterComponent>([&](auto const& e, auto& m) {
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
			auto pickaxe = scene.spawnEntity("pickaxe");
			auto& h = pickaxe.get<engine::HitboxComponent>();
			auto& t = pickaxe.get<engine::TransformComponent>();
			engine::GeometryHelper::transformHitbox(h, t);
			auto item = entity.attach(pickaxe);
			hc.items[++hc.current] = item;
			hc.count += 1;

			scene.registerEvent<std::string>("player.move", entity.getId(), [&](std::string const& move) {
				auto _move = (Vector2f)move;
				physicsComponent.move = _move;

				if (_move.x > 0)
					transformComponent.direction = true;
				else if (_move.x < 0)
					transformComponent.direction = false;
				return 0;
			});

			scene.registerEvent<std::string>("player.jump", entity.getId(), [entity, &scene, &physicsComponent, &animationComponent, &hc](std::string const& jump) {
				if (engine::PhysicsSystem::isGrounded(scene.getEntities(), entity)) {
					physicsComponent.velocity += (Vector2f) jump;
					animationComponent.currentState = PlayerSystem::getState("jump", hc);
					animationComponent.playOnce = true;
					animationComponent.nextState = PlayerSystem::getState("inAir", hc);
				}

				return 0;
			});

			scene.registerEvent<std::string>("player.pick", entity.getId(), [entity, &hc](std::string const& s) {
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
			//
			scene.registerEvent<std::string>("player.use", entity.getId(), [entity, &hc](std::string const& s) {
				engine::Entity& item = hc.items[hc.current];
				if (hc.current >= 0) {
					if (item.has<engine::ItemComponent>()) {
						item.get<engine::ItemComponent>().use();
					}
				}
				return 0;
			});

			scene.registerEvent<std::string>("player.aim", entity.getId(), [entity, &hc](std::string const& move) {
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

			scene.registerEvent<std::string>("player.play", entity.getId(), [&game, &scene, entity](std::string const&) {
				game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_Q, "player.move", entity.getId(), Vector2f(-10.f, 0.f), engine::EVT_SYNCED | engine::EVT_OVERRIDE);
				game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_Q, "player.move", entity.getId(), Vector2f(0.f, 0.f), engine::EVT_SYNCED | engine::EVT_RELEASE);
				game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_D, "player.move", entity.getId(), Vector2f(10.f, 0.f), engine::EVT_SYNCED | engine::EVT_OVERRIDE);
				game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_D, "player.move", entity.getId(), Vector2f(0.f, 0.f), engine::EVT_SYNCED | engine::EVT_RELEASE);
				game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_SPACE, "player.jump", entity.getId(), Vector2f(0.f, 70.f), engine::EVT_SYNCED | engine::EVT_OVERRIDE);
				game.eventsHandler.subscribe<std::string>(scene, engine::KeyCode::KEY_KEY_R, "player.pick", entity.getId(), "0", engine::EVT_SYNCED | engine::EVT_OVERRIDE);
				game.eventsHandler.subscribe<std::string>(scene, engine::KeyCode::KEY_KEY_S, "player.use", entity.getId(), "0", engine::EVT_SYNCED | engine::EVT_OVERRIDE);
				game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_UP, "player.aim", entity.getId(), Vector2f(0.f, 1.f), engine::EVT_SYNCED | engine::EVT_OVERRIDE);
				game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_RIGHT, "player.aim", entity.getId(), Vector2f(1.f, 0.f), engine::EVT_SYNCED | engine::EVT_OVERRIDE);
				game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_DOWN, "player.aim", entity.getId(), Vector2f(0.f, -1.f), engine::EVT_SYNCED | engine::EVT_OVERRIDE);
				game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_LEFT, "player.aim", entity.getId(), Vector2f(-1.f, 0.f), engine::EVT_SYNCED | engine::EVT_OVERRIDE);

				return 0;
			});

			return 0;
		});

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
			transform.position = {14.f, 10.f, 0.f};
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
                static int id = 0;
                std::string texture;
                ++id;
                id %= 3;
                if (id == 1) {
                    texture = "texture/player_anonymous.png";
                } else if (id == 2) {
                    texture = "texture/player_dali.png";
                } else {
                    texture = "texture/player_anonymous.png";
                }
				entity.get<engine::TransformComponent>().position = (Vector3f)pos;
				entity.get<engine::IrrlichtComponent>().node->setMaterialTexture(0, engine::ResourceManager<engine::Texture*>::instance().get(texture));
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
		scene.spawnEntity("background");
		scene.spawnEntity("timer");

		for (auto i = 0; i < 2; ++i) {
			scene.triggerEvent<std::string>("player.spawn", 0, Vector3f(10.f * i - 5.f, 25.f, 0.f).serialize());
		}

		scene.triggerEvent<std::string>("master.changePlayer", 0, "0");
	};
}}
