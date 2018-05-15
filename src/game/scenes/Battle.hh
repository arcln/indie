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

namespace worms {

	namespace scene {

		static const auto battle = [](engine::Game& game, engine::Scene& scene) {
			scene.registerEntityModel("map", [&](engine::Entity const& entity) {
				entity.addComponent<engine::DisplayComponent>(&game, "plant.md3").node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			});

			scene.registerEntityModel("worm", [&](engine::Entity const& entity) {
				auto& displayComponent = entity.addComponent<engine::DisplayComponent>(&game, "plant.md3");
				displayComponent.node->setPosition(irr::core::vector3df {250 - (std::rand() % 500), -250.f + (std::rand() % 500), 0});
				displayComponent.node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
			});

			scene.registerEntityModel("blue_light", [&](engine::Entity const& entity) {
				auto& lightComponent = entity.addComponent<engine::LightComponent>(game.device(), irr::core::vector3df(0, 500, 50), irr::video::SColorf(0.0f, 0.0f, 1.0f), 1000);
			});

			scene.registerEvent<engine::GenericEvent>("test", [&](engine::GenericEvent const&) {
				scene.spawnEntity("worm");
				return 0;
			});

			game.eventsHandler.subscribe([&](engine::KeyState const& keystate) -> int {
				if (keystate.Key == engine::KeyCode::KEY_KEY_E && keystate.PressedDown) {
					scene.triggerEvent<engine::GenericEvent>("test");
				}

				return 0;
			});

//			scene.spawnEntity("map");
			scene.spawnEntity("blue_light");
		};
	}
}
