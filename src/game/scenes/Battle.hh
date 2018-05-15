//
//  BattleSceneModel.hpp
//  engine
//
//  Created by Arthur Chaloin on 14/05/2018.
//

#pragma once

#include <iostream>
#include "engine/core/Scene.hpp"
#include "engine/core/Event.hpp"

namespace worms {

	namespace scene {

		static const auto battle = [](engine::Game& game, engine::Scene& scene) {
			scene.registerEntityModel("map", [&](engine::Entity const& entity) {
				entity.addComponent<engine::DisplayComponent>(&game, "plant.md3");
			});

			scene.registerEntityModel("worm", [&](engine::Entity const& entity) {
				auto& displayComponent = entity.addComponent<engine::DisplayComponent>(&game, "plant.md3");
				displayComponent.node->setPosition(irr::core::vector3df {0.f, -100.f + (std::rand() % 200), 200.f});
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

			scene.spawnEntity("map");
		};
	}
}
