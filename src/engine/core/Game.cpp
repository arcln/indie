/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include "Game.hpp"

engine::Game::Game()
{
}

engine::Game::~Game()
{
}

void
engine::Game::play(engine::Scene& scene)
{
	while (scene.isRunning()) {
		scene.update();
	}
}
