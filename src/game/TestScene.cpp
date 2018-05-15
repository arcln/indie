/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include <iostream>
#include <engine/components/CameraComponent.hpp>
#include "TestScene.hpp"

testGame::TestScene::TestScene(engine::Game* game, bool isServer) : _game(game), _isServer(isServer)
{}

testGame::TestScene::~TestScene()
{}

engine::Game::SceneModel
testGame::TestScene::getSceneModel()
{
	return [&](engine::Scene& scene) -> engine::Scene& {
		scene.registerEntityModel("map", [&](engine::Entity const& entity) -> engine::Entity const& {
			entity.addComponent<engine::DisplayComponent>(_game, "plant.md3");
			return entity;
		});

		scene.registerEntityModel("camera", [&](engine::Entity const& entity) -> engine::Entity const& {
			entity.addComponent<engine::CameraComponent>(_game->device(), engine::CameraComponent::Coords(0, 0, -500));
			return entity;
		});

		scene.registerEvent<int>("display map", [&](void const*) {
			scene.spawnEntity("map");
		});

		_game->eventsHandler.subscribe([&](engine::KeyState const& keystate) -> int {
			if (keystate.Key == engine::KeyCode::KEY_KEY_E && keystate.PressedDown) {
				scene.triggerEvent<int>("display map", 0);
			}

			return 0;
		});

//		if (!_isServer) {
//			scene.synchonizeWith("localhost");
//			_cns = std::make_unique<engine::ClientNetworkSystem>(scene.socket, scene.events);
//			_game->registerSystem("network", _cns.get());
//		}

		scene.triggerEvent<int>("display map", 0);
		scene.spawnEntity("camera");
		return scene;
	};
}
