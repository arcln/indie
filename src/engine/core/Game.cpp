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
engine::Game::play(std::string const& name)
{
	this->pushScene(name);

	while (_device->run() && !_scenes.empty()) {
		_updateScenes();
	}
}

void engine::Game::replaceScene(std::string const& name)
{
	if (!_scenes.empty()) {
		_scenes.clear();
	}

	this->pushScene(name);
}

void engine::Game::pushScene(std::string const& name)
{
	engine::Scene scene;

	if (_sceneModels.find(name) == std::end(_sceneModels))
		throw std::runtime_error("scene model '" + name + "' not found");

	_scenes.push_back(_sceneModels[name](scene));
}

void engine::Game::popScene()
{
	_scenes.pop_back();
}

void
engine::Game::registerSystem(std::string const& name, System* system)
{
	_systems[name] = system;
}

void engine::Game::registerSceneModel(std::string const& name, engine::Game::SceneModel const& sceneModel)
{
	_sceneModels[name] = sceneModel;
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

void engine::Game::_updateScenes()
{
	for (auto& scene : _scenes) {
		for (auto& system : _systems) {
			system.second->update(scene.getEntities());
		}
	}

}
