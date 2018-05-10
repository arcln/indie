/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include "Game.hpp"

engine::Game::Game()
{
	_device = irr::createDevice(irr::video::EDT_SOFTWARE,
								irr::core::dimension2d<irr::u32>(1280, 720),
								16, false, false, false, 0);
	if (!_device) {
		throw std::runtime_error("fatal: failed to initialize irrlicht");
	}
}

engine::Game::~Game()
{
}

void
engine::Game::play(engine::Scene& scene)
{
	while (_device->run() && scene.isRunning()) {
		scene.update();
	}
}

irr::IrrlichtDevice&
engine::Game::device()
{
	return *_device;
}

irr::IrrlichtDevice const&
engine::Game::device() const
{
	return *_device;
}
