//
//  BattleSceneModel.hpp
//  engine
//
//  Created by Arthur Chaloin on 14/05/2018.
//

#pragma once

#include <iostream>
#include <engine/components/LightComponent.hpp>
#include <engine/components/ComponentFilter.hpp>
#include <engine/components/IrrlichtComponent.hpp>
#include <engine/components/HitboxComponent.hpp>
#include <engine/components/TransformComponent.hpp>
#include "engine/components/CameraComponent.hpp"
#include "engine/core/Scene.hpp"
#include "engine/core/Event.hpp"

namespace worms { namespace scene {

	static const auto battle = [](engine::Game& game, engine::Scene& scene) {
		scene.registerEntityModel("camera", [&](engine::Entity const& entity) {
			auto& cameraComponent = entity.set<engine::CameraComponent>(game.device(),
										    engine::CameraComponent::Coords {
											    0.f, 0.f, -10.0},
										    engine::CameraComponent::Coords {0.0,
														     0,
														     0.0}
			);

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

		scene.registerEntityModel("map", [&](engine::Entity const& entity) {
			auto& IrrlichtComponent = entity.set<engine::IrrlichtComponent>(&game, "obj/map.obj");
			IrrlichtComponent.node->setPosition(irr::core::vector3df {0.f, 0.f, 0.f});
			IrrlichtComponent.node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			IrrlichtComponent.node->setMD2Animation(irr::scene::EMAT_STAND);
			IrrlichtComponent.node->setMaterialTexture(0, game.textureManager.get("texture/map.png"));

			entity.get<engine::IrrlichtComponent,
				engine::IrrlichtComponent>([](engine::IrrlichtComponent const& irrlichtComponent,
							    engine::IrrlichtComponent const& irrlichtComponent2) {
			});
		});

		scene.registerEntityModel("worm", [&](engine::Entity const& entity) {
			auto& irrlichtComponent = entity.set<engine::IrrlichtComponent>(&game, "obj/worm.obj", "texture/worm.png");

            auto& transformComponent = entity.set<engine::TransformComponent>();
            // transformComponent.scale = {2.5f, 2.5f, 2.5f};
            transformComponent.position = {0.f, 0.f, 0.f};

			auto& hitboxComponent = entity.set<engine::HitboxComponent>("(-1 0, -1 4, 1 4, 1 0)");
            hitboxComponent.hasDebugMode = true;

			scene.registerEvent<engine::CameraComponent::Coords>("move player", [&](auto const& offset) {
                //
				// irrlichtComponent.node->setRotation(irr::core::vector3df {0.f, offset.X < 0 ? 270.f : 90.f, 0.f});
				// irrlichtComponent.node->setPosition(irrlichtComponent.node->getPosition() + offset);
				// scene.triggerEvent("set camera lookat", irrlichtComponent.node->getPosition());
				return 0;
			});
		});

        scene.registerEntityModel("worm2", [&](engine::Entity const& entity) {
			auto& irrlichtComponent = entity.set<engine::IrrlichtComponent>(&game, "obj/worm.obj", "texture/worm.png");

            auto& transformComponent = entity.set<engine::TransformComponent>();
            transformComponent.scale = {.5f, .5f, .5f};
            transformComponent.position = {3.f, 3.f, 3.f};

			auto& hitboxComponent = entity.set<engine::HitboxComponent>("(-1 0, -1 4, 1 4, 1 0)");
            hitboxComponent.hasDebugMode = true;

			scene.registerEvent<engine::CameraComponent::Coords>("move player", [&](auto const& offset) {
				irrlichtComponent.node->setRotation(irr::core::vector3df {0.f, offset.X < 0 ? 270.f : 90.f, 0.f});
				irrlichtComponent.node->setPosition(irrlichtComponent.node->getPosition() + offset);
				scene.triggerEvent("set camera lookat", irrlichtComponent.node->getPosition());
				return 0;
			});
		});

		scene.registerEntityModel("blue light", [&](engine::Entity const& entity) {
			entity.set<engine::LightComponent>(game.device(), irr::core::vector3df(0, 500, 50),
							   irr::video::SColorf(0.0f, 0.0f, 1.0f), 1000);
		});

		scene.registerEvent<engine::GenericEvent>("spawn worm", [&](engine::GenericEvent const&) {
			scene.spawnEntity("worm");
			return 0;
		});

		game.eventsHandler.subscribe([&](engine::KeyState const& keystate) -> int {
			if (keystate.PressedDown) {
				switch (keystate.Key) {
					case engine::KeyCode::KEY_KEY_Q:
						scene.triggerEvent<engine::CameraComponent::Coords>("move player", {-1.f, 0.f, 0.f});
						break;
					case engine::KeyCode::KEY_KEY_D:
						scene.triggerEvent<engine::CameraComponent::Coords>("move player", {1.f, 0.f, 0.f});
						break;
					case engine::KeyCode::KEY_KEY_E:
						scene.triggerEvent<engine::GenericEvent>("spawn worm");
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
					default: break;
				}
			}

			return 0;
		});

		scene.spawnEntity("blue light");
		scene.spawnEntity("camera");
        scene.spawnEntity("worm");
		scene.spawnEntity("worm2");
		// scene.spawnEntity("map");
	};
}}
