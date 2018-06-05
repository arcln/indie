//
//  Worms.hh
//  worms
//
//  Created by Arthur Chaloin on 30/05/2018.
//

#pragma once

#include "engine/core/Game.hpp"
#include "engine/systems/DisplaySystem.hpp"
#include "engine/systems/PhysicsSystem.hpp"
#include "game/scenes/Battle.hh"

namespace worms {

	static const auto worms = [](engine::Game& game) {
        game.registerSystem("physics", new engine::PhysicsSystem());
        game.registerSystem("display", new engine::DisplaySystem(game));

		game.registerSceneModel("main", worms::scene::test);
		game.registerSceneModel("battle", worms::scene::battle);
	};
}
