/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include <string>
#include "engine/core/Scene.hpp"
#include "engine/core/Game.hpp"
#include "engine/systems/ClientNetworkSystem.hpp"

std::size_t engine::Scene::_LastSceneId = 0;

engine::Scene::Scene() : _running(true), _synced(false), _id(++_LastSceneId)
{
}

engine::Scene::~Scene()
{
}

void
engine::Scene::registerEntityModel(std::string const& name, EntityModel const& model)
{
	_models[name] = model;
}

engine::Entity
engine::Scene::spawnEntity(std::string const& name, EntityId parentId)
{
	if (_models.find(name) == std::end(_models))
		throw std::runtime_error("entity model '" + name + "' not found");

	return _entities.add(parentId, _models[name]);
}

engine::Entity
engine::Scene::spawnEntity(std::string const& name, EntityModel const& initialisation, EntityId parentId)
{
	engine::Entity entity = this->spawnEntity(name, parentId);
	initialisation(entity);
	return entity;
}

bool
engine::Scene::isRunning() const
{
	return _running;
}

void
engine::Scene::previousScene()
{
	_running = false;
}

std::size_t
engine::Scene::id() const
{
	return _id;
}

bool
engine::Scene::hasEvent(std::string const& eventName) const
{
	return _events.find(eventName) != std::end(_events);
}

engine::Entities&
engine::Scene::getEntities()
{
	return _entities;
}

void
engine::Scene::deleteEvent(std::string const& evt, EntityId id)
{
	_events[evt]->unsubscribe(id);
}

void
engine::Scene::synchronizeWith(std::string const& hostname, Game& game)
{
	_socket.create().connect(hostname);

	_socket.send<network::TextMessage>(engine::network::version);
	auto res = _socket.receive<engine::network::TextMessage>();

	if (std::string(res.text) != engine::network::version) {
		throw std::runtime_error(std::string("server version ") + res.text + " does not match current version " + engine::network::version);
	}
	std::cerr << "worms: network: successfuly connected to " << hostname << std::endl;

	game.registerSystem(new ClientNetworkSystem(_socket, _events));
	_synced = true;
}
