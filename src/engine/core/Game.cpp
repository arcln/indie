/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include "engine/systems/System.hpp"
#include "Game.hpp"

engine::Game::Game()
{
	_device = irr::createDevice(irr::video::EDT_OPENGL,
								irr::core::dimension2d<irr::u32>(1280, 720),
								16, false, false, false, 0);
	if (!_device) {
		throw std::runtime_error("fatal: failed to initialize irrlicht");
	}
	_device->setWindowCaption(L"Worms 3D");

	this->meshManager.onLoad([&](std::string const& asset) {
		return this->_device->getSceneManager()->getMesh(asset.c_str());
	});
}

engine::Game::~Game()
{
}

void
engine::Game::play(engine::Scene& scene)
{
	engine::Components<engine::DisplayComponent> components;
	components.emplace(0, new engine::DisplayComponent(*this, "plant.md3"));

	while (_device->run() && scene.isRunning()) {
		for (auto& s : _systems) {
			s.second->update(components);
		}

		scene.update();
	}
}

void
engine::Game::registerSystem(std::string const& name, System* system)
{
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
