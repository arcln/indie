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
#include <unordered_map>
#include <map>
#include <engine/Event.hpp>
#include "Entity.hpp"

namespace engine {

	class Scene {
	public:
		Scene();
		virtual ~Scene();

		virtual void update() = 0;

		using EntityEdition = std::function<void (Entity const&)>;

		Entity& makeModel(std::string const &name);
		Entity& makeModel(std::string const &name, EntityEdition const &composition);
		Entity& spawnEntity(std::string const &name);
		Entity& spawnEntity(std::string const &name, EntityEdition const &initialisation);

		bool isRunning() const;

	protected:
		void previousScene();

	private:
		std::vector<Entity> _entities;
		std::unordered_map<ComponentType, std::map<EntityId, Component>, ComponentTypeHash> _components;

		bool _running;
	};
}
