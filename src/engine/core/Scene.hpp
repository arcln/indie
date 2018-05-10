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
#include "engine/core/Event.hpp"
#include "engine/core/Entity.hpp"

namespace engine {

	using Models = std::unordered_map<std::string, Entity>;

	using Entities = std::unordered_map<EntityId, Entity>;

	/**
	 * Holds models, entities and components.
	 */
	class Scene {
	public:
		Scene(class Game* device);
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
		Entity const& registerModel(std::string const& name, EntityEdition const& composition);

		/**
		 * Spawn an entity based on the model designated by his name
		 * @param name Model's name
		 * @return the spawned entity
		 */
		EntityId spawnEntity(std::string const& name);

		/**
		 * Spawn an entity based on the model designated by his name
		 * @param name Model's name
		 * @param initialisation Function that modify the spawned entity
		 * @return the spawned entity
		 */
		EntityId spawnEntity(std::string const& name, EntityEdition const& initialisation);

		/**
		 * Get an entity by its id
		 * @param id Entity's id
		 * @return the entity
		 */
		Entity const& getEntity(EntityId id) const;

		bool isRunning() const;

		ComponentPool componentPool;

	protected:
		void previousScene();

		class Game* _game;

	private:
		Entities _entities;
		Models _models;

		bool _running = true;
	};
}
