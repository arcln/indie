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
#include "engine/network/Socket.hpp"
#include "engine/network/Message.hpp"

int
main()
{
	engine::Game game;

	try {
		engine::DisplaySystem display(game);
		game.registerSystem("display", &display);

		testGame::TestScene scene(&game);
		game.registerSceneModel("main", scene.getSceneModel());
		game.play("main");
	} catch (std::exception& e) {
		std::cerr << "worms: ERROR: " << e.what() << std::endl;
	}

	return 0;
}
