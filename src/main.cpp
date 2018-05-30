/*
** EPITECH PROJECT, 2018
** worms
** File description:
** main.cpp
*/

#include "engine/Engine.hpp"
#include "game/Worms.hh"

int main()
{
	engine::Engine engine(WORMS_IS_SERVER);

	std::cerr << "worms: starting " << (WORMS_IS_SERVER ? "server" : "client") << std::endl;
	return engine.play(worms::worms);
}
