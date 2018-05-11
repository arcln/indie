/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include "engine/core/Game.hpp"
#include "engine/core/Scene.hpp"

namespace testGame {

	class TestScene : public engine::Scene {
	public:
		TestScene(engine::Game* game);
		virtual ~TestScene();
	};
}
