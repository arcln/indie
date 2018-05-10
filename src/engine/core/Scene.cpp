/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include "Scene.hpp"

engine::Scene::Scene(engine::Game* game) : _game(game), _running(true)
{
}

engine::Scene::~Scene()
{
}

engine::Entity&
engine::Scene::registerModel(std::string const& name)
{
	auto entityIt = _models.emplace(name, engine::Entity(&this->componentPool));

	if (!entityIt.second)
		throw std::runtime_error("unable to register a model");

	return entityIt.first->second;
}

engine::Entity const&
engine::Scene::registerModel(std::string const& name, EntityEdition const& composition)
{
	return composition(registerModel(name));
}

engine::EntityId
engine::Scene::spawnEntity(std::string const& name)
{
	if (_models.find(name) == std::end(_models))
		throw std::runtime_error("model '" + name + "' not found");
	auto entity = Entity(&this->componentPool);
	_entities[entity.getId()] = std::move(entity);
	return _entities[entity.getId()].copyComponents(_models[name]).getId();
}


engine::EntityId
engine::Scene::spawnEntity(std::string const& name, EntityEdition const& initialisation)
{
	return initialisation(this->getEntity(spawnEntity(name))).getId();
}

engine::Entity const&
engine::Scene::getEntity(EntityId id) const
{
	return _entities.at(id);
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
