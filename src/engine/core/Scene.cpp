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
	auto entity = Entity(&this->componentPool);
	_entities[entity.getId()] = _models[name](entity);
	return entity.getId();
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
