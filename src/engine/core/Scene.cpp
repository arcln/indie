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

engine::EntityId engine::Scene::_LastSpawnedEntityId = engine::Entity::nullId;
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

engine::Entity const&
engine::Scene::spawnEntity(std::string const& name, EntityId parentId)
{
	if (_models.find(name) == std::end(_models))
		throw std::runtime_error("entity model '" + name + "' not found");


	return _entities.add(engine::Entity(++_LastSpawnedEntityId, parentId, &_entities), _models[name]);
}

engine::Entity const&
engine::Scene::spawnEntity(std::string const& name, EntityModel const& initialisation, EntityId parentId)
{
	engine::Entity const& entity = this->spawnEntity(name, parentId);
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
	return this->events.find(eventName) != std::end(this->events);
}

engine::Entities const&
engine::Scene::getEntities() const
{
	return _entities;
}

void
engine::Scene::synchronizeWith(std::string const& hostname, Game& game)
{
	this->socket.create().connect(hostname);

	this->socket.send<network::TextMessage>(engine::network::version);
	auto res = this->socket.receive<engine::network::TextMessage>();

	if (std::string(res.text) != engine::network::version) {
		throw std::runtime_error(std::string("server version ") + res.text + " does not match current version " + engine::network::version);
	}
	std::cout << "worms: network: successfuly connected to " << hostname << std::endl;

	game.registerSystem("network", new ClientNetworkSystem(this->socket, this->events));
	_synced = true;
}
