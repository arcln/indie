/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include <string>
#include "engine/core/Scene.hpp"
#include "engine/core/Game.hpp"

engine::EntityId engine::Scene::_lastSpawnedEntityId = engine::Entity::nullId;

engine::Scene::Scene() : _running(true)
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

engine::EntityId
engine::Scene::spawnEntity(std::string const& name)
{
	if (_models.find(name) == std::end(_models))
		throw std::runtime_error("entity model '" + name + "' not found");

	_entities.add(_models[name](engine::Entity(++_lastSpawnedEntityId, engine::Entity::nullId, &_entities)));
	return _lastSpawnedEntityId;
}

engine::EntityId
engine::Scene::spawnEntity(std::string const& name, EntityModel const& initialisation)
{
	EntityId entityId = this->spawnEntity(name);

	initialisation(Entity(entityId, engine::Entity::nullId, &_entities));
	return entityId;
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

engine::Entities const&
engine::Scene::getEntities() const
{
	return _entities;
}

void
engine::Scene::synchonizeWith(std::string const& hostname)
{
	_socket.create().connect(hostname);

	_socket.send<std::string>("v0.1");
	auto res = _socket.receive<engine::network::TextMessage>();

	if (std::string(res.text) != "v0.1") {
		throw std::runtime_error(std::string("server version ") + res.text + " does not match current version v0.1");
	}

	std::cout << "worms: network: successfuly connected to " << hostname << std::endl;
}
