//
//  BattleSceneModel.hpp
//  engine
//
//  Created by Arthur Chaloin on 14/05/2018.
//

#pragma once

#include <iostream>
#include <engine/components/LightComponent.hpp>
#include "engine/core/Scene.hpp"
#include "engine/core/Event.hpp"
#include "engine/components/CameraComponent.hpp"

namespace worms { namespace scene {

	static const auto battle = [](engine::Game& game, engine::Scene& scene) {
		scene.registerEntityModel("camera", [&](engine::Entity const& entity) {
			auto& cameraComponent = entity.addComponent<engine::CameraComponent>(game.device(),
										engine::CameraComponent::Coords {0.f, 0.f, -10.f},
										engine::CameraComponent::Coords {0, 0, 0}
									);

			scene.registerEvent<engine::CameraComponent::Coords>("set camera position", [&](auto const& position) {
				cameraComponent.node->setPosition(position);
				return 0;
			});

			scene.registerEvent<engine::CameraComponent::Coords>("move camera", [&](auto const& offset) {
				cameraComponent.node->setPosition(cameraComponent.node->getPosition() + offset);
				return 0;
			});
		});

		scene.registerEntityModel("map", [&](engine::Entity const& entity) {
			auto& displayComponent = entity.addComponent<engine::DisplayComponent>(&game, "map.dae");
			displayComponent.node->setPosition(irr::core::vector3df {0.f, 0.f, 0.f});
			displayComponent.node->setScale(irr::core::vector3df {10.f, 10.f, 100.f});
			displayComponent.node->setRotation(irr::core::vector3df {0.f, 90.f, 0.f});
		});

		scene.registerEntityModel("worm", [&](engine::Entity const& entity) {
			auto& displayComponent = entity.addComponent<engine::DisplayComponent>(&game, "worm/worm.obj");
			displayComponent.node->setPosition(irr::core::vector3df {0.f, -3.f, 0.f});
			displayComponent.node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			displayComponent.node->setMD2Animation(irr::scene::EMAT_STAND);
			displayComponent.node->setMaterialTexture(0, game.textureManager.get("worm/body.png.001.png"));

//			irr::scene::IMeshCache* cache = game.device()->getSceneManager()->getMeshCache();
//
//			for (auto i = 1u; i < cache->getMeshCount(); i++) {
//				auto* node = game.device()->getSceneManager()->addAnimatedMeshSceneNode(cache->getMeshByIndex(i));
//				node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
//				node->setMD2Animation(irr::scene::EMAT_STAND);
//				node->setMaterialTexture(0, game.textureManager.get("worm/body.png.001.png"));
//			}

			scene.registerEvent<engine::CameraComponent::Coords>("move player", [&](auto const& offset) {
				displayComponent.node->setRotation(irr::core::vector3df {0.f, offset.X < 0 ? 270.f : 90.f, 0.f});
				displayComponent.node->setPosition(displayComponent.node->getPosition() + offset);
				return 0;
			});
		});

		scene.registerEntityModel("blue light", [&](engine::Entity const& entity) {
			auto& lightComponent = entity.addComponent<engine::LightComponent>(game.device(), irr::core::vector3df(0, 500, 50), irr::video::SColorf(0.0f, 0.0f, 1.0f), 1000);
			return 0;
		});

		scene.registerEvent<engine::GenericEvent>("test", [&](engine::GenericEvent const&) {
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
						scene.triggerEvent<engine::GenericEvent>("test");
						break;
					case engine::KeyCode::KEY_RIGHT:
						scene.triggerEvent<engine::CameraComponent::Coords>("move camera", {0.f, 0.f, -0.5f});
						break;
					case engine::KeyCode::KEY_LEFT:
						scene.triggerEvent<engine::CameraComponent::Coords>("move camera", {0.f, 0.f, 0.5f});
						break;
					case engine::KeyCode::KEY_UP:
						scene.triggerEvent<engine::CameraComponent::Coords>("move camera", {0.f, 0.5f, 0.f});
						break;
					case engine::KeyCode::KEY_DOWN:
						scene.triggerEvent<engine::CameraComponent::Coords>("move camera", {0.f, -0.5f, 0.f});
						break;
					case engine::KeyCode::KEY_KEY_R:
						scene.triggerEvent<engine::CameraComponent::Coords>("move camera", {0.5f, 0.f, 0.f});
						break;
					case engine::KeyCode::KEY_KEY_F:
						scene.triggerEvent<engine::CameraComponent::Coords>("move camera", {-0.5f, 0.f, 0.f});
						break;
					default: break;
				}
			}

			return 0;
		});

		scene.spawnEntity("blue light");
		scene.spawnEntity("camera");
		scene.spawnEntity("worm");
		scene.spawnEntity("map");
	};
}}
