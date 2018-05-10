/*
** EPITECH PROJECT, 2018
** worms
** File description:
** main.cpp
*/

#include <iostream>
#include <string>
#include "engine/core/Event.hpp"
#include "engine/core/Scene.hpp"
#include "game/TestScene.hpp"
#include "engine/core/Game.hpp"
#include "engine/components/DisplayComponent.hpp"
#include "engine/systems/DisplaySystem.hpp"

int
main(int const, char const *[])
{
	engine::Game game;

//	try {
		engine::DisplaySystem display(game);
		game.registerSystem("display", &display);

		testGame::TestScene scene;
		game.play(scene);
//	} catch (std::exception& e) {
//		std::cerr << "worms: ERROR: " << e.what() << std::endl;
//	}

	return 0;
}
