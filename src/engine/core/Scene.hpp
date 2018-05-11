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

	/**
	 * Holds models, entities and components.
	 */
	class Scene {
	public:
		Scene();
		virtual ~Scene();

		using EntityModel = std::function<Entity const& (Entity const&)>;
		using EntityModels = std::unordered_map<std::string, EntityModel>;

		/**
		 * Register a model to spawn it later
		 * @param name Name of the model to register
		 * @param model Function that model an entity
		 * @return the model
		 */
		void registerEntityModel(std::string const& name, EntityModel const& model);

		/**
		 * Spawn an entity based on the model designated by its name
		 * @param name Model's name
		 * @return the spawned entity
		 */
		EntityId spawnEntity(std::string const& name);

		/**
		 * Spawn an entity based on the model designated by its name
		 * @param name Model's name
		 * @param initialisation Function that modify the spawned entity
		 * @return the spawned entity
		 */
		EntityId spawnEntity(std::string const& name, EntityModel const& initialisation);

		Entities const& getEntities() const;

		bool isRunning() const;

	protected:
		void previousScene();

	private:
		static EntityId _lastSpawnedEntityId;

		EntityModels _models;
		Entities _entities;
		bool _running;
	};
}
