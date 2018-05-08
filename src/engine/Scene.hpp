/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include <vector>
#include <string>
#include <functional>
#include <bits/unordered_map.h>
#include <map>
#include "Entity.hpp"

namespace engine {

	class Scene {
	public:
		virtual ~Scene();

		virtual void update() = 0;

		using EntityEdition = std::function<bool, Entity const&>;

		void makeModel(std::string const &name, EntityEdition &composition);
		void spawnEntity(std::string const &name, EntityEdition &initialisation); // TODO initialisation default parameter

	private:
		std::vector<Entity> _entities;
		std::unordered_map<ComponentType, std::map<EntityId, Component>> _components;
	};
}
