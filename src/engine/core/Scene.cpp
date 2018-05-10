#include "Scene.hpp"

/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

engine::Scene::Scene() : _running(true)
{
}

engine::Scene::~Scene()
{
}

engine::Entity&
engine::Scene::registerModel(std::string const& name)
{
	auto entityIt = _models.emplace(name, engine::Entity(_componentPool));

	if (!entityIt.second)
		throw std::runtime_error("unable to register a model");

	return entityIt.first->second;
}

engine::Entity const&
engine::Scene::registerModel(std::string const& name, EntityEdition const& composition)
{
	return composition(registerModel(name));
}

engine::Entity const&
engine::Scene::spawnEntity(std::string const& name)
{
	if (_models.find(name) == std::end(_models))
		throw std::runtime_error("model \"" + name + "\" not found");
	_entities.emplace_back(_models[name]);
	return _entities.back();
}


engine::Entity const&
engine::Scene::spawnEntity(std::string const& name, EntityEdition const &initialisation)
{
	initialisation(spawnEntity(name));
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

engine::ComponentPool&
engine::Scene::getComponentPool()
{
	return _componentPool;
}

engine::ComponentPool
const& engine::Scene::getComponentPool() const
{
	return _componentPool;
}
