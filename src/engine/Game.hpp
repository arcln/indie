/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include "Scene.hpp"

namespace engine {

	class Game {
	public:
		Game() = default;
		virtual ~Game() = default;

		void play(Scene &scene);
	};
}

