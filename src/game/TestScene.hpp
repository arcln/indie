/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include <memory>
#include "engine/core/Game.hpp"
#include "engine/core/Scene.hpp"
#include "engine/systems/ClientNetworkSystem.hpp"

namespace testGame {

	class TestScene {
	public:
		TestScene(engine::Game* game, bool isServer = false);
		virtual ~TestScene();

		engine::Game::SceneModel getSceneModel();

	private:
		std::unique_ptr<engine::ClientNetworkSystem> _cns;
		engine::Game* _game;
		bool _isServer;
	};
}
