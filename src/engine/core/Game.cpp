/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include <unistd.h>
#include "System.hpp"
#include "Game.hpp"

engine::Game::Game(bool enableVideo, std::string const& cwd)
	: eventsHandler(_keyEvents)
	, _eventReceiver(_keyEvents)
	, _cwd(cwd)
{
	_device = irr::createDevice(enableVideo ? irr::video::EDT_OPENGL : irr::video::EDT_NULL,
								irr::core::dimension2d<irr::u32>(1280, 720), 16, false, false, false,
								&_eventReceiver);

	if (!_device) {
		throw std::runtime_error("fatal: failed to initialize irrlicht");
	}
	_device->setWindowCaption(L"Worms");

	ResourceManager<MeshNode*>::instance().loadFrom(cwd).onLoad([&](std::string const& asset) {
		return this->device()->getSceneManager()->getMesh(asset.c_str());
	});

	ResourceManager<Texture*>::instance().loadFrom(cwd).onLoad([&](std::string const& asset) {
		return this->device()->getVideoDriver()->getTexture(asset.c_str());
	});
}

engine::Game::~Game()
{
	_device->drop();
}

void
engine::Game::play(std::string const& name)
{
	this->pushScene(name);

	while (!_scenes.empty()) {
		if (!_device->run()) {
			return;
		}

		_updateScenes();
	}
}

void
engine::Game::replaceScene(std::string const& name)
{
	if (!_scenes.empty()) {
		_scenes.clear();
	}
	engine::internal::componentPoolReset.emit(true);
	this->pushScene(name);
}

void
engine::Game::pushScene(std::string const& name)
{
	if (_sceneModels.find(name) == std::end(_sceneModels)) {
		throw std::runtime_error("scene model '" + name + "' not found");
	}

	_scenes.emplace_back();
	_sceneModels[name](*this, _scenes.back());
}

void
engine::Game::popScene()
{
	this->eventsHandler.unregisterEventTarget(_scenes.back());
	_scenes.pop_back();
}

void
engine::Game::registerSystem(std::string const& name, System* system)
{
	if (_systems[name] != nullptr) {
		delete system;
	}

	_systems[name] = system;
}

void
engine::Game::registerSceneModel(std::string const& name, engine::Game::SceneModel const& sceneModel)
{
	_sceneModels[name] = sceneModel;
}

irr::IrrlichtDevice*
engine::Game::device()
{
	return _device;
}

irr::IrrlichtDevice const*
engine::Game::device() const
{
	return _device;
}

std::string const&
engine::Game::getcwd() const
{
	return _cwd;
}

void engine::Game::_updateScenes()
{
	for (auto& scene : _scenes) {
		for (auto& system : _systems) {
			system.second->update(scene);
		}
	}
}
