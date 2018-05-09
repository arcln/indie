/*
** EPITECH PROJECT, 2018
** worms
** File description:
** main.cpp
*/

#include <iostream>
#include <string>
#include "engine/Event.hpp"

int main()
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

	return 0;
}
