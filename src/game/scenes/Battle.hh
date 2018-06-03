//
//  BattleSceneModel.hpp
//  engine
//
//  Created by Arthur Chaloin on 14/05/2018.
//

#pragma once

#include <iostream>
#include "engine/core/Game.hpp"
#include <engine/components/LightComponent.hpp>
#include <engine/components/ComponentFilter.hpp>
#include <engine/components/IrrlichtComponent.hpp>
#include <engine/components/HitboxComponent.hpp>
#include <engine/components/TransformComponent.hpp>
#include <engine/components/TagComponent.hpp>
#include "engine/components/CameraComponent.hpp"
#include "engine/components/PhysicsComponent.hpp"
#include "engine/components/AnimationComponent.hpp"
#include "engine/components/TagComponent.hpp"
#include "engine/core/Scene.hpp"
#include "engine/core/Event.hpp"
#include "game/events/Vector.hpp"

namespace worms { namespace scene {

	static const auto battle = [](engine::Game& game, engine::Scene& scene) {
		scene.registerEntityModel("camera", [&](engine::Entity const& entity) {
			auto& cameraComponent = entity.set<engine::CameraComponent>(game.device(),
										engine::CameraComponent::Coords {0.f, 0.f, -10.f}, engine::CameraComponent::Coords {0, 0, 0}
			);

            entity.set<engine::TransformComponent>();


			scene.registerEvent<engine::CameraComponent::Coords>("set camera position", [&](auto const& position) {
				cameraComponent.node->setPosition(position);
				return 0;
			});

			scene.registerEvent<engine::CameraComponent::Coords>("set camera lookat", [&](auto const& position) {
				cameraComponent.node->setTarget(position);
				return 0;
			});

			scene.registerEvent<engine::CameraComponent::Coords>("move camera", [&](auto const& offset) {
				cameraComponent.node->setPosition(cameraComponent.node->getPosition() + offset);
				cameraComponent.node->setTarget(cameraComponent.node->getTarget() + offset);
				return 0;
			});
		});
        //
		// scene.registerEntityModel("map", [&](engine::Entity const& entity) {
		// 	auto& IrrlichtComponent = entity.set<engine::IrrlichtComponent>(&game, "obj/map.obj");
		// 	IrrlichtComponent.node->setPosition(irr::core::vector3df {0.f, 0.f, 0.f});
		// 	IrrlichtComponent.node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		// 	IrrlichtComponent.node->setMD2Animation(irr::scene::EMAT_STAND);
		// 	IrrlichtComponent.node->setMaterialTexture(0, game.textureManager.get("texture/map.png"));
        //
		// 	entity.get<engine::IrrlichtComponent,
		// 		engine::IrrlichtComponent>([](engine::IrrlichtComponent const& irrlichtComponent,
		// 					    engine::IrrlichtComponent const& irrlichtComponent2) {
		// 	});
		// });

		scene.registerEntityModel("block", [&](engine::Entity const& entity) {
			entity.set<engine::IrrlichtComponent>(&game, "obj/block.obj");

            auto& transformComponent = entity.set<engine::TransformComponent>();
            transformComponent.position = {0.f, 0.f, 0.f};

			auto& hitboxComponent = entity.set<engine::HitboxComponent>("(-50 -10, -50 20, -28 20, -28 4, -20 1, -10 1, 1 2, 1 -10)");
            hitboxComponent.hasDebugMode = true;

		});

        scene.registerEntityModel("worm", [&](engine::Entity const& entity) {
			entity.set<engine::IrrlichtComponent>(&game, "obj/worm.obj", "texture/worm.png");

            std::cout << "worms id: " << entity.getId() << std::endl;

            auto& physicsComponent = entity.set<engine::PhysicsComponent>();
            auto& transformComponent = entity.set<engine::TransformComponent>();
            transformComponent.scale = {.5f, .5f, .5f};
            transformComponent.position = {0.f, 25.f, 0.f};

			auto& hitboxComponent = entity.set<engine::HitboxComponent>("(-1 0, -1 4, 1 4, 1 0)");
            hitboxComponent.hasDebugMode = true;

            scene.registerEvent<engine::Vec2D>("jump player", [&](auto const& jump) {
                // if (physicsComponent.velocity == engine::Vec2D{0.f, 0.f})
                    physicsComponent.velocity += jump;
				// irrlichtComponent.node->setRotation(irr::core::vector3df {0.f, offset.X < 0 ? 270.f : 90.f, 0.f});
				// irrlichtComponent.node->setPosition(irrlichtComponent.node->getPosition() + offset);
				// scene.triggerEvent("set camera lookat", irrlichtComponent.node->getPosition());
				return 0;
			});

			scene.registerEvent<engine::Vec2D>("move player", [&](auto const& offset) {
                physicsComponent.velocity += offset;
                // transformComponent.position.X += offset.X;
                // transformComponent.position.Y += offset.Y;
				// irrlichtComponent.node->setRotation(irr::core::vector3df {0.f, offset.X < 0 ? 270.f : 90.f, 0.f});
				// irrlichtComponent.node->setPosition(irrlichtComponent.node->getPosition() + offset);
				// scene.triggerEvent("set camera lookat", irrlichtComponent.node->getPosition());
				return 0;
			});
		});

		scene.registerEntityModel("light", [&](engine::Entity const& entity) {
			entity.set<engine::LightComponent>(game.device(), irr::core::vector3df(0, 500, 50),
							   irr::video::SColorf(0.0f, 0.0f, 0.0f), 1000);
		});

		scene.registerEvent<engine::GenericEvent>("spawn worm", [&](engine::GenericEvent const&) {
			scene.spawnEntity("worm");
			return 0;
		});

		game.eventsHandler.subscribe([&](engine::KeyState const& keystate) -> int {
			if (keystate.PressedDown) {
				switch (keystate.Key) {
                    case engine::KeyCode::KEY_KEY_Z:
						scene.triggerEvent<engine::Vec2D>("jump player", {-0.f, 100.f});
						break;
					case engine::KeyCode::KEY_KEY_Q:
						scene.triggerEvent<engine::Vec2D>("move player", {-20.f, 0.f});
						break;
					case engine::KeyCode::KEY_KEY_D:
						scene.triggerEvent<engine::Vec2D>("move player", {20.f, 0.f});
						break;
					case engine::KeyCode::KEY_KEY_E:
						scene.triggerSyncedEvent<Vector3f>("spawn worm", Vector3f(0.f, 0.f, 0.f));
						break;
					case engine::KeyCode::KEY_RIGHT:
						scene.triggerEvent<engine::CameraComponent::Coords>("move camera", {-1.f, 0.f, 0.f});
						break;
					case engine::KeyCode::KEY_LEFT:
						scene.triggerEvent<engine::CameraComponent::Coords>("move camera", {1.f, 0.f, 0.f});
						break;
					case engine::KeyCode::KEY_UP:
						scene.triggerEvent<engine::CameraComponent::Coords>("move camera", {0.f, 1.f, 0.f});
						break;
					case engine::KeyCode::KEY_DOWN:
						scene.triggerEvent<engine::CameraComponent::Coords>("move camera", {0.f, -1.f, 0.f});
						break;
					case engine::KeyCode::KEY_KEY_R:
						scene.triggerEvent<engine::CameraComponent::Coords>("move camera", {0.f, 0.f, 1.f});
						break;
					case engine::KeyCode::KEY_KEY_F:
						scene.triggerEvent<engine::CameraComponent::Coords>("move camera", {0.f, 0.f, -1.f});
						break;
					case engine::KeyCode::KEY_KEY_O:
						scene.triggerEvent<bool>("anim1", true);
						break;
					case engine::KeyCode::KEY_KEY_P:
						scene.triggerEvent<bool>("anim2", true);
						break;
					default: break;
				}
			}

			return 0;
		});
		scene.spawnEntity("light");
		scene.spawnEntity("camera");
        scene.spawnEntity("block");
        scene.spawnEntity("worm");
		// scene.spawnEntity("map");
	};
}}
