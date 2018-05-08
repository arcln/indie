/*
** EPITECH PROJECT, 2018
** worms
** File description:
** main.cpp
*/

#include <iostream>
#include <string>
#include "engine/Event.hpp"
#include "engine/Scene.hpp"
#include "testGame/TestScene.hpp"
#include "engine/Game.hpp"

int
main(int const, char const *[])
{
	engine::Event<std::string, std::string> event;

	event.subscribe([](std::string const& payload) -> std::string {
		std::cout << "1 Event was triggered, payload contains: " << payload << std::endl;
		return "response 1";
	});

	event.subscribe([](std::string const& payload) -> std::string {
		std::cout << "2 Event was triggered, payload contains: " << payload << std::endl;
		return "response 2";
	});

	event.emit("payload", [](std::string const& response) -> void {
		std::cout << "Response: " << response << std::endl;
	});

	engine::Game game;
	engine::Scene scene = testGame::TestScene();

	game.play(scene);
	return 0;
}
