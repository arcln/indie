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
#include <engine/Event.hpp>
#include "Entity.hpp"

namespace engine {

	using Models = std::unordered_map<std::string, Entity>;

	using Entities = std::vector<Entity>;

	/**
	 * Holds models, entities and components.
	 */
	class Scene {
	public:
		Scene();
		virtual ~Scene();

		virtual void update() = 0;

		using EntityEdition = std::function<void (Entity const&)>;

		Entity& registerModel(std::string const& name);
		Entity& registerModel(std::string const& name, EntityEdition const& composition);
		Entity& spawnEntity(std::string const &name);
		Entity& spawnEntity(std::string const &name, EntityEdition const &initialisation);

		bool isRunning() const;
		ComponentPool& getComponentPool();
		const ComponentPool& getComponentPool() const;

	protected:
		void previousScene();

	private:
		Entities _entities;
		Models _models;
		ComponentPool _componentPool;

		bool _running;
	};
}
