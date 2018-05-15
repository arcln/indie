//
//  BattleSceneModel.hpp
//  engine
//
//  Created by Arthur Chaloin on 14/05/2018.
//

#pragma once

#include <iostream>
#include "engine/core/Scene.hpp"

namespace worms {

	namespace scene {

		static const auto battle = [](engine::Game& game, engine::Scene& scene) {
			scene.registerEntityModel("map", [&](engine::Entity const& entity) -> engine::Entity const& {
				auto& displayComponent = entity.addComponent<engine::DisplayComponent>();
				displayComponent.init(&game, "plant.md3");
				return entity;
			});

			scene.registerEntityModel("worm", [&](engine::Entity const& entity) -> engine::Entity const& {
				auto& displayComponent = entity.addComponent<engine::DisplayComponent>();
				displayComponent.init(&game, "plant.md3");
				displayComponent.node->setPosition(irr::core::vector3df {0.f, -100.f, 200.f});
				return entity;
			});

			scene.registerEvent<int>("test", [](int const& val) {
				std::cout << val << std::endl;
				return 0;
			});

			game.eventsHandler.subscribe([&](engine::KeyState const& keystate) -> int {
				if (keystate.Key == engine::KeyCode::KEY_KEY_E && keystate.PressedDown) {
					scene.triggerEvent<int>("test", 42);
				}

				return 0;
			});

			scene.spawnEntity("map");
			scene.spawnEntity("worm");
		};
	}
}
