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
#include "game/components/MasterComponent.hpp"
#include "game/components/PlayerComponent.hpp"
#include "game/events/Vector.hpp"

namespace worms { namespace scene {

		static const auto battle = [](engine::Game& game, engine::Scene& scene) {

			engine::Entity master(engine::Entity::nullId, engine::Entity::nullId, &scene.getEntities());
			master.set<MasterComponent>().currentPlayer = 0;

			scene.registerEntityModel("camera", [&](engine::Entity const& entity) {
				entity.set<engine::TransformComponent>();

				auto& cameraComponent = entity.set<engine::CameraComponent>(
					game.device(), engine::CameraComponent::Coords {0.f, 0.f, -30.f}, engine::CameraComponent::Coords {0, 0, 0}
				);

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

				game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_RIGHT, "camera.move", entity.getId(), Vector3f(-1.f, 0.f, 0.f));
				game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_LEFT,  "camera.move", entity.getId(), Vector3f(1.f, 0.f, 0.f));
				game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_UP,    "camera.move", entity.getId(), Vector3f(0.f, 1.f, 0.f));
				game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_DOWN,  "camera.move", entity.getId(), Vector3f(0.f, -1.f, 0.f));
				game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_KEY_R, "camera.move", entity.getId(), Vector3f(0.f, 0.f, 1.f));
				game.eventsHandler.subscribe<Vector3f>(scene, engine::KeyCode::KEY_KEY_F, "camera.move", entity.getId(), Vector3f(0.f, 0.f, -1.f));
			});

			scene.registerEntityModel("player", [&](engine::Entity const& entity) {
				entity.set<PlayerComponent>(0);
				entity.set<engine::IrrlichtComponent>(&game, "obj/silinoid.ms3d");

				auto& physicsComponent = entity.set<engine::PhysicsComponent>();
				auto& transformComponent = entity.set<engine::TransformComponent>();
				auto& animationComponent = entity.set<engine::AnimationComponent>("idle");
				animationComponent.states.emplace("run", engine::AnimationBoundaries(0, 40));
				animationComponent.states.emplace("idle", engine::AnimationBoundaries(40, 80));
				animationComponent.states.emplace("jump", engine::AnimationBoundaries(230, 19));
				animationComponent.states.emplace("inAir", engine::AnimationBoundaries(240, 9)); // TODO

				transformComponent.scale = {0.5f, 0.5f, 0.5f};
				transformComponent.position = {0.f, 25.f, 0.f};

				auto& hitboxComponent = entity.set<engine::HitboxComponent>("(-1 0, -1 4, 1 4, 1 0)");
				hitboxComponent.hasDebugMode = true;
				hitboxComponent.rebound = 0.1f;

				auto& hc = entity.set<engine::HoldComponent>();

//				auto& animationComponent = entity.set<engine::AnimationComponent>("idle");
//				animationComponent.states.emplace("run", engine::AnimationBoundaries(0, 40));
//				animationComponent.states.emplace("idle", engine::AnimationBoundaries(40, 79));

				scene.registerEvent<std::string>("player.move", entity.getId(), [&](std::string const& move) {
                    auto _move = (Vector2f)move;
					physicsComponent.move = _move;

                    if (_move.x > 0)
                        transformComponent.direction = true;
                    else if (_move.x < 0)
                        transformComponent.direction = false;

					if (physicsComponent.move.X < 0) {
						transformComponent.rotation.Y = 180;
					} else if (physicsComponent.move.X > 0) {
						transformComponent.rotation.Y = 0;
					}

					return 0;
				});

				scene.registerEvent<std::string>("player.jump", entity.getId(), [entity, &scene, &physicsComponent, &animationComponent](std::string const& jump) {
					if (engine::PhysicsSystem::isGrounded(scene.getEntities(), entity)) {
						std::cout << "jump" << std::endl;
						physicsComponent.velocity += (Vector2f) jump;
						animationComponent.currentState = "jump";
						animationComponent.playOnce = true;
						animationComponent.nextState = "inAir";
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

				scene.registerEvent<std::string>("player.use", entity.getId(), [entity, &hc](std::string const& s) {
					if (hc.current >= 0) {
						engine::Entity& item = hc.items[hc.current];
						if (item.has<engine::ItemComponent>()) {
							item.get<engine::ItemComponent>().use();
						}
					}
					return 0;
				});

				// scene.registerEvent<std::string>("player.explode", entity.getId(), [&](std::string const& move) {
				//     for (int i = 0; i < 4; i++)
				//     Wornite::Map::tryDestroyMap(scene, transformComponent.position.X, transformComponent.position.Y, 2.f);
				//     std::cout << "end" << std::endl;
				//     return 0;
				// });

				scene.registerEvent<std::string>("player.hitbox", entity.getId(), [&](std::string const& move) {
					static bool DebugMode = false;
					engine::Entities entities = scene.getEntities();
					entities.withTag("map", [&](engine::Entity const& chunk) {
						entities.eachChilds(chunk.getId(), [&](engine::Entity const &child) {
							auto& h = child.get<engine::HitboxComponent>();

							h.hasDebugMode = DebugMode;
						});
					});
					DebugMode = !DebugMode;
					return 0;
				});

				game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_Q, "player.move", entity.getId(), Vector2f(-10.f, 0.f), engine::EVT_SYNCED);
				game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_Q, "player.move", entity.getId(), Vector2f(0.f, 0.f), engine::EVT_SYNCED | engine::EVT_RELEASE);
				game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_D, "player.move", entity.getId(), Vector2f(10.f, 0.f), engine::EVT_SYNCED);
				game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_D, "player.move", entity.getId(), Vector2f(0.f, 0.f), engine::EVT_SYNCED | engine::EVT_RELEASE);
				game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_SPACE, "player.jump", entity.getId(), Vector2f(0.f, 100.f), engine::EVT_SYNCED);
				game.eventsHandler.subscribe<std::string>(scene, engine::KeyCode::KEY_KEY_R, "player.pick", entity.getId(), "0", engine::EVT_SYNCED);
				game.eventsHandler.subscribe<std::string>(scene, engine::KeyCode::KEY_KEY_U, "player.use", entity.getId(), "0", engine::EVT_SYNCED);
				game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_X, "player.explode", entity.getId(), Vector2f(0.f, 0.f), engine::EVT_SYNCED);
				game.eventsHandler.subscribe<Vector2f>(scene, engine::KeyCode::KEY_KEY_H, "player.hitbox", entity.getId(), Vector2f(0.f, 0.f), engine::EVT_SYNCED);

				return 0;
		});



        scene.registerEntityModel("item", [&](engine::Entity const& entity) {
            entity.set<engine::IrrlichtComponent>(&game, "obj/block.obj");
            entity.set<engine::PhysicsComponent>();
			auto& ic = entity.set<engine::ItemComponent>([]() {
                std::cout << "use item" << std::endl;
            });

            ic.offset = {1.f, 2.f, 0.f};
            auto& transformComponent = entity.set<engine::TransformComponent>();
            transformComponent.position = {-10.f, 10.f, 0.f};
            transformComponent.scale = {0.5f, 0.5f, 0.5f};
		});

		scene.registerEntityModel("light", [&](engine::Entity const& entity) {
			entity.set<engine::LightComponent>(
				game.device(), irr::core::vector3df(0, 500, 50), irr::video::SColorf(0.0f, 0.0f, 0.0f), 1000
			);
		});

        scene.registerEntityModel("item", [&](engine::Entity const& entity) {
            entity.set<engine::IrrlichtComponent>(&game, "obj/block.obj");
            entity.set<engine::PhysicsComponent>();
			auto& ic = entity.set<engine::ItemComponent>([]() {
                std::cout << "use item" << std::endl;
            });

            ic.offset = {1.f, 2.f, 0.f};

			auto& transformComponent = entity.set<engine::TransformComponent>();
			transformComponent.position = {-10.f, 10.f, 0.f};
            transformComponent.scale = {0.5f, 0.5f, 0.5f};

			auto& hitboxComponent = entity.set<engine::HitboxComponent>("(-1 -1, -1 1, 1 1, 1 -1)");
			hitboxComponent.rebound = 0.2;
			hitboxComponent.hasDebugMode = true;
		});

        scene.registerEntityModel("sword", [&](engine::Entity const& entity) {
            entity.set<engine::IrrlichtComponent>(&game, "obj/sword.obj", "obj/sword.mtl");
            entity.set<engine::PhysicsComponent>();


			auto& transformComponent = entity.set<engine::TransformComponent>();
			transformComponent.position = {10.f, 10.f, 0.f};
            transformComponent.scale = {0.25f, 0.25f, 0.25f};
            transformComponent.offset = {0.f, -5.8f, 0.f};
            transformComponent.offsetRotation = {0.f, -90.f, 0.f};

			auto& hitboxComponent = entity.set<engine::HitboxComponent>("(-6 -1.5, -6 1.5, 6 1.5, 6 -1.5)");
			hitboxComponent.rebound = 0.2;
			hitboxComponent.hasDebugMode = true;

            auto& ic = entity.set<engine::ItemComponent>();
            ic.use = [&]() {
                std::cout << "use item" << std::endl;
                auto bullet = scene.spawnEntity("sword.bullet");
                auto& bt = bullet.get<engine::TransformComponent>();
                auto& bp = bullet.get<engine::PhysicsComponent>();
                bt.position = transformComponent.position;
                bp.velocity.X = 300.f;
                if (!ic.direction)
                    bp.velocity.X *= -1;
            };
            ic.offset = {1.5f, 1.f, 0.f};
		});

        scene.registerEntityModel("sword.bullet", [&](engine::Entity const& entity) {
            entity.set<engine::IrrlichtComponent>(&game, "obj/block.obj");
            entity.set<engine::PhysicsComponent>();

			auto& transformComponent = entity.set<engine::TransformComponent>();
            transformComponent.scale = {0.25f, 0.25f, 0.25f};
			auto& hitboxComponent = entity.set<engine::HitboxComponent>("(-1 -1, -1 1, 1 1, 1 -1)");
            hitboxComponent.onCollide = [entity, &scene, &transformComponent](engine::Entity const& collideWith) -> void {
                Wornite::Map::tryDestroyMap(scene, transformComponent.position.X, transformComponent.position.Y, 2.f);
                entity.disable(); // TODO: kill
            };
            hitboxComponent.hasDebugMode = true;
		});

        scene.registerEntityModel("item", [&](engine::Entity const& entity) {
            entity.set<engine::IrrlichtComponent>(&game, "obj/block.obj");
            entity.set<engine::PhysicsComponent>();
			auto& ic = entity.set<engine::ItemComponent>([]() {
                std::cout << "use item" << std::endl;
            });

            ic.offset = {1.f, 2.f, 0.f};

			auto& transformComponent = entity.set<engine::TransformComponent>();
			transformComponent.position = {-10.f, 10.f, 0.f};
            transformComponent.scale = {0.5f, 0.5f, 0.5f};

			auto& hitboxComponent = entity.set<engine::HitboxComponent>("(-1 -1, -1 1, 1 1, 1 -1)");
			hitboxComponent.rebound = 0.8;
			hitboxComponent.hasDebugMode = true;
		});

		scene.registerEntityModel("light", [&](engine::Entity const& entity) {
			entity.set<engine::LightComponent>(
				game.device(), irr::core::vector3df(0, 500, 50), irr::video::SColorf(0.0f, 0.0f, 0.0f), 1000
			);
		});

		scene.registerEvent<std::string>("player.spawn", 0, [&](std::string const&) {
            scene.spawnEntity("item");
			scene.spawnEntity("player");
			return 0;
		});

		scene.registerEvent<std::string>("master.changePlayer", 0, [&](std::string const& player) {
			scene.getEntities().each<MasterComponent>([&](engine::Entity const& e, auto& m) {
				m.currentPlayer = std::stoi(player);
				if (m.currentPlayer != 0) { //TODO: Replace by player id
					game.eventsHandler.disableKeyEvent(engine::KeyCode::KEY_KEY_D);
					game.eventsHandler.disableKeyEvent(engine::KeyCode::KEY_KEY_Q);
					game.eventsHandler.disableKeyEvent(engine::KeyCode::KEY_SPACE);
				} else {
					game.eventsHandler.enableKeyEvent(engine::KeyCode::KEY_KEY_D);
					game.eventsHandler.enableKeyEvent(engine::KeyCode::KEY_KEY_Q);
					game.eventsHandler.enableKeyEvent(engine::KeyCode::KEY_SPACE);
				}
			});

			return 0;
		});

		Wornite::Map().genMap(game, scene);

		game.eventsHandler.subscribe<std::string>(scene, engine::KeyCode::KEY_KEY_E, "player.spawn", 0, std::to_string(1));
		game.eventsHandler.subscribe<std::string>(scene, engine::KeyCode::KEY_KEY_P, "master.changePlayer", 0, std::to_string(1));
		game.eventsHandler.subscribe<std::string>(scene, engine::KeyCode::KEY_KEY_O, "master.changePlayer", 0, std::to_string(0));

		scene.spawnEntity("camera");
		scene.spawnEntity("player");
		scene.spawnEntity("light");
		scene.spawnEntity("item");
		scene.spawnEntity("sword");
	};
}}
