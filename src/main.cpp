/*
** EPITECH PROJECT, 2018
** worms
** File description:
** main.cpp
*/

#include <iostream>
#include <string>
#include "engine/Event.hpp"
#include "engine/core/Scene.hpp"
#include "game/TestScene.hpp"
#include "engine/core/Game.hpp"
#include "engine/components/TestComponent.hpp"
#include "engine/systems/DisplaySystem.hpp"

int
main(int const, char const *[])
{
	engine::Game game;
	engine::DisplaySystem display(game);
	engine::Components components;

	while (true) {
		display.update(components);
	}

	return 0;
}
