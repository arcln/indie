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

engine::Entity& engine::Scene::makeModel(std::string const& name)
{
	// TODO register a model to spawn it later
}

engine::Entity& engine::Scene::makeModel(std::string const& name, EntityEdition const &composition)
{
	composition(makeModel(name));
}

engine::Entity& engine::Scene::spawnEntity(std::string const& name)
{
	// TODO create an entity based on the name corresponding model
}

engine::Entity& engine::Scene::spawnEntity(std::string const& name, EntityEdition const &initialisation)
{
	initialisation(spawnEntity(name));
}

bool engine::Scene::isRunning() const
{
	return _running;
}

void engine::Scene::previousScene()
{
	_running = false;
}
