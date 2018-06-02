/*
** EPITECH PROJECT, 2018
** worms
** File description:
** main.cpp
*/

#include "engine/core/Game.hpp"
#include "engine/systems/PhysicsSystem.hpp"
#include "engine/systems/DisplaySystem.hpp"

#include "game/scenes/Battle.hh"

namespace worms {

	void start() {
		engine::Game game;

		engine::DisplaySystem display(game);
        engine::PhysicsSystem physics;

        game.registerSystem("physics", &physics);
		game.registerSystem("display", &display);

		game.registerSceneModel("battle", worms::scene::battle);
		game.play("battle");
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
