//
//  Worms.hh
//  worms
//
//  Created by Arthur Chaloin on 30/05/2018.
//

#pragma once

#include "engine/core/Game.hpp"
#include "engine/systems/DisplaySystem.hpp"
#include "game/scenes/Battle.hh"

namespace worms {

	static const auto worms = [](engine::Game& game) {
		game.registerSystem("display", new engine::DisplaySystem(game));
		game.registerSceneModel("main", worms::scene::battle);
	};
}
