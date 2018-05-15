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
#include "engine/core/Game.hpp"
#include "engine/components/DisplayComponent.hpp"
#include "engine/systems/ServerNetworkSystem.hpp"
#include "engine/network/Socket.hpp"
#include "engine/network/Message.hpp"
#include "engine/network/Selector.hpp"

void sighandler(int signum) {
	exit(0);
}

using namespace engine::network;

int
main()
{
//	signal(SIGINT, &sighandler);
//
//	engine::Game game(false);
//
//	try {
//		testGame::TestScene scene(&game, true);
//		engine::ServerNetworkSystem networkSystem;
//
//		game.registerSystem("network", &networkSystem);
//		game.registerSceneModel("main", scene.getSceneModel());
//		game.play("main");
//	} catch (std::exception& e) {
//		std::cerr << "worms-server: ERROR: " << e.what() << std::endl;
//	}
//
//	return 0;
}
