/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include "engine/systems/System.hpp"
#include "Game.hpp"

engine::Game::Game() : _eventReceiver(_keyEvents), _eventHandler(_keyEvents)
{
	_device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1280, 720), 16, false, false, false, &_eventReceiver);
	if (!_device) {
		throw std::runtime_error("fatal: failed to initialize irrlicht");
	}
	_device->setWindowCaption(L"Worms 3D");

	this->meshManager.onLoad([&](std::string const& asset) {
		return this->_device->getSceneManager()->getMesh(asset.c_str());
	});

	_eventHandler.subscribe([&](KeyState const& keyState) -> int {
		if (keyState.Key == engine::KeyCode::KEY_ESCAPE && !keyState.PressedDown)
			_device->closeDevice();
		return 0;
	});
}

engine::Game::~Game()
{
}

void
engine::Game::play(engine::Scene& scene)
{
	this->pushScene(scene);

	while (_device->run() && !_scenes.empty()) {
		for (auto& s : _systems) {
			s.second->update();
		}
	}
}

void engine::Game::replaceScene(engine::Scene& scene)
{
	if (!_scenes.empty())
		_scenes = std::stack<engine::Scene>();

	_scenes.push(scene);
}

void engine::Game::pushScene(engine::Scene& scene)
{
	_scenes.push(scene);
}

void engine::Game::popScene()
{
	_scenes.pop();
}

void
engine::Game::registerSystem(std::string const& name, System* system)
{
	_systems[name] = system;
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
