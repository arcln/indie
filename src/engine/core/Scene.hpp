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

		using EntityEdition = std::function<Entity const& (Entity const&)>;

		/**
		 * Register a model to spawn it later
		 * @param name Name of the model to register
		 * @return the model
		 */
		Entity& registerModel(std::string const& name);

		/**
		 * Register a model to spawn it later
		 * @param name Name of the model to register
		 * @param composition Function that model an entity
		 * @return the model
		 */
		const Entity& registerModel(std::string const& name, EntityEdition const& composition);

		/**
		 * Spawn an entity based on the model designated by his name
		 * @param name Model's name
		 * @return the spawned entity
		 */
		const Entity& spawnEntity(std::string const &name);

		/**
		 * Spawn an entity based on the model designated by his name
		 * @param name Model's name
		 * @param initialisation Function that modify the spawned entity
		 * @return the spawned entity
		 */
		const Entity& spawnEntity(std::string const &name, EntityEdition const &initialisation);

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
