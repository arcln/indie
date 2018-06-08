/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Menu Main Cpp
*/

#include "engine/core/Game.hpp"
#include "engine/core/Scene.hpp"
#include "engine/systems/DisplaySystem.hpp"
#include "engine/menu/classes/system/MenuEngineSystem.hpp"

#include "scene/PostMenu.hh"
#include "scene/MainMenu.hh"
#include "scene/TestScene.hh"
#include "scene/OptionsMenu.hh"
#include "scene/KeyAssign.hh"

namespace worms {

	void start() {
		engine::Game game(true, "../assets/");
		engine::DisplaySystem display(game);
		engine::Menu::MenuEngineSystem effects;
		game.registerSystem("display", &display);
		game.registerSystem("effects", &effects);

		game.registerSceneModel("postMenu", worms::scene::postMenu);
		game.registerSceneModel("mainMenu", worms::scene::mainMenu);
		game.registerSceneModel("testScene", worms::scene::testScene);
		game.registerSceneModel("optionsMenu", worms::scene::optionsScene);
		game.registerSceneModel("keyAssign", worms::scene::keyAssign);
		game.play("postMenu");
	}
}

int main()
{
	try {
		worms::start();
	} catch (std::exception& e) {
		std::cerr << "worms: ERROR: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
