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

	class TestScene {
	public:
		TestScene(engine::Game* game);
		virtual ~TestScene();

		engine::Game::SceneModel getSceneModel();

	private:
		engine::Game* _game;
		engine::Game::SceneModel _scene;
	};
}
