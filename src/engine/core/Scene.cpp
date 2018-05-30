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
engine::Scene::spawnEntity(std::string const& name, EntityId parentId)
{
	if (_models.find(name) == std::end(_models))
		throw std::runtime_error("entity model '" + name + "' not found");

	_entities.add(engine::Entity(++_lastSpawnedEntityId, parentId, &_entities), _models[name]);
	return _lastSpawnedEntityId;
}

engine::EntityId
engine::Scene::spawnEntity(std::string const& name, EntityModel const& initialisation, EntityId parentId)
{
	EntityId entityId = this->spawnEntity(name, parentId);

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
	this->socket.create().connect(hostname);

	this->socket.send<engine::network::TextMessage>(engine::network::version);
	auto res = this->socket.receive<engine::network::TextMessage>();

	if (std::string(res.text) != engine::network::version) {
		throw std::runtime_error(std::string("server version ") + res.text + " does not match current version " + engine::network::version);
	}

	std::cout << "worms: network: successfuly connected to " << hostname << std::endl;
}
