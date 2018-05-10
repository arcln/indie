/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include <iostream>
#include "DisplaySystem.hpp"
#include "engine/components/DisplayComponent.hpp"

engine::DisplaySystem::DisplaySystem(engine::Game& game) : _game(game)
{
	_driver = _game.device().getVideoDriver();
	_smgr = _game.device().getSceneManager();
	_guienv = _game.device().getGUIEnvironment();

	_smgr->addCameraSceneNode(0, irr::core::vector3df(0, 30, -40), irr::core::vector3df(0, 5, 0));
}

void
engine::DisplaySystem::update(Components<DisplayComponent>&)
{
	_game.device().run();
	_driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

	_smgr->drawAll();
	_guienv->drawAll();

	_driver->endScene();
}

engine::DisplaySystem::~DisplaySystem()
{
	_game.device().drop();
}
