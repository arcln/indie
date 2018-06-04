/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Menu Main Cpp
*/

#include "engine/core/Game.hpp"
#include "engine/core/Scene.hpp"
#include "engine/systems/DisplaySystem.hpp"

#include "scene/PostMenu.hh"
#include "scene/MainMenu.hh"
#include "scene/TestScene.hh"

namespace worms {

	void start() {
		engine::Game game(true, "../assets/");
		engine::DisplaySystem display(game);
		game.registerSystem("display", &display);

		game.registerSceneModel("postMenu", worms::scene::postMenu);
		game.registerSceneModel("mainMenu", worms::scene::mainMenu);
		game.registerSceneModel("testScene", worms::scene::testScene);
		game.play("testScene");
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
