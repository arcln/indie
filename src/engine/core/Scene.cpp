/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

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
engine::Scene::registerModel(std::string const& name, EntityEdition const& composition)
{
	_models[name] = composition;
}

engine::EntityId
engine::Scene::spawnEntity(std::string const& name)
{
	if (_models.find(name) == std::end(_models))
		throw std::runtime_error("model '" + name + "' not found");

	_entities.emplace(engine::Entity::nullId, _models[name](engine::Entity(++_lastSpawnedEntityId, engine::Entity::nullId, &_entities, &componentPool)));
	return _lastSpawnedEntityId;
}

engine::EntityId
engine::Scene::spawnEntity(std::string const& name, EntityEdition const& initialisation)
{
	EntityId entityId = this->spawnEntity(name);

	initialisation(Entity(entityId, engine::Entity::nullId, &_entities, &componentPool));
	return entityId;
}

// TODO getEntity

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
