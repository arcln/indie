/*
** EPITECH PROJECT, 2018
** worms
** File description:
** main.cpp
*/

#include <iostream>
#include <string>
#include <csignal>
#include "engine/core/Event.hpp"
#include "engine/core/Scene.hpp"
#include "game/TestScene.hpp"
#include "engine/core/Game.hpp"
#include "engine/components/DisplayComponent.hpp"
#include "engine/systems/DisplaySystem.hpp"
#include "engine/network/Socket.hpp"
#include "engine/network/Message.hpp"
#include "engine/network/Selector.hpp"

void sighandler(int signum) {
	exit(0);
}

using namespace engine::network;

int
main(int const, char const *[])
{
	signal(SIGINT, &sighandler);

	Selector master;
	
	master.onData<TextMessage>([](ClientSocket const& client, void* msg) {
		std::cout << reinterpret_cast<TextMessage*>(msg)->text << std::endl;
	});

	master.run().join();

	std::cout << "all clients connected." << std::endl;
	while (true);


//	engine::Game game;
//
//	try {
//		engine::DisplaySystem display(game);
//		game.registerSystem("display", &display);
//
//		testGame::TestScene scene(&game);
//		game.play(scene);
//	} catch (std::exception& e) {
//		std::cerr << "worms: ERROR: " << e.what() << std::endl;
//	}


	return 0;
}
