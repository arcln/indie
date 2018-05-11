/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include "engine/core/Game.hpp"
#include "engine/systems/DisplaySystem.hpp"

engine::DisplaySystem::DisplaySystem(engine::Game& game) : _game(game)
{
	std::cout << "ok" << std::endl;
	_videoDriver = _game.device().getVideoDriver();
	_sceneManager = _game.device().getSceneManager();
	_guiEnv = _game.device().getGUIEnvironment();

	_sceneManager->addCameraSceneNode(0, irr::core::vector3df(0, 30, -40), irr::core::vector3df(0, 5, 0));
}

void
engine::DisplaySystem::update(Entities const&)
{
	_game.device().run();
	_videoDriver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

	_sceneManager->drawAll();
	_guiEnv->drawAll();

	_videoDriver->endScene();
}

engine::DisplaySystem::~DisplaySystem()
{
	_game.device().drop();
}
