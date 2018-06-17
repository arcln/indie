//
//  Worms.hh
//  worms
//
//  Created by Arthur Chaloin on 30/05/2018.
//

#pragma once

#include "engine/systems/TimeoutSystem.hpp"
#include "engine/core/Game.hpp"
#include "engine/systems/ItemSystem.hpp"
#include "engine/systems/DisplaySystem.hpp"
#include "engine/systems/PhysicsSystem.hpp"
#include "game/systems/PlayerSystem.hpp"
#include "game/systems/WeaponSystem.hpp"
#include "engine/systems/MenuEngineSystem.hpp"
#include "game/scenes/Battle.hh"
#include "game/scenes/Loading.hh"
#include "game/scenes/PostMenu.hh"
#include "game/scenes/MainMenu.hh"
#include "game/scenes/PlayMenu.hh"
#include "game/scenes/OptionsMenu.hh"
#include "game/scenes/CreditsMenu.hh"
#include "game/scenes/WaitingMenu.hh"
#include "game/scenes/KeyAssign.hh"
#include "game/scenes/GameOver.hh"

namespace worms {

	static const auto worms = [](engine::Game& game) {
        game.registerSystem("item", new engine::ItemSystem());
        game.registerSystem("physics", new engine::PhysicsSystem());
		game.registerSystem("display", new engine::DisplaySystem(game));
		game.registerSystem("timeout", new engine::TimeoutSystem());
		game.registerSystem("player", new PlayerSystem());
        game.registerSystem("weapon", new WeaponSystem(game));
		game.registerSystem("effects", new engine::Menu::MenuEngineSystem());

		game.registerSceneModel("postMenu", worms::scene::postMenu);
		game.registerSceneModel("mainMenu", worms::scene::mainMenu);
		game.registerSceneModel("playMenu", worms::scene::playScene);
		game.registerSceneModel("creditsMenu", worms::scene::creditsScene);
		game.registerSceneModel("optionsMenu", worms::scene::optionsScene);
		game.registerSceneModel("keyAssign", worms::scene::keyAssign);
		game.registerSceneModel("waintingMenu", worms::scene::waitingScene);
		game.registerSceneModel("main", worms::scene::loading);
		game.registerSceneModel("battle", worms::scene::battle);
		game.registerSceneModel("gameOver", worms::scene::gameOver);
	};
}
