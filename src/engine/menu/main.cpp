/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Menu Main Cpp
*/

#include "engine/core/Game.hpp"
#include "engine/core/Scene.hpp"
#include "engine/systems/DisplaySystem.hpp"

#include "scene/Menu.hh"

namespace worms {

	void start() {
		engine::Game game;
		engine::DisplaySystem display(game);
		game.registerSystem("display", &display);

		game.registerSceneModel("menu", worms::scene::menu);
		game.play("menu");
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
