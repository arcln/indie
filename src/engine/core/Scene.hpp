/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include <vector>
#include <string>
#include <typeinfo>
#include <functional>
#include <unordered_map>
#include <map>
#include "engine/core/Event.hpp"
#include "engine/core/Entity.hpp"
#include "engine/core/Entities.hpp"
#include "engine/network/Message.hpp"

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
		using EventHandler = std::function<void (void const*)>;

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

		template <typename ContextType>
		void registerEvent(std::string const& name, EventHandler const& handler) {
			_eventHandlers[name] = handler;
			_events[name].subscribe([&](std::string const& context) -> int {
				// TODO: Deserialize context
				_eventHandlers[name](&context);
				return 0;
			});
		}

		template <typename ContextType>
		void triggerEvent(std::string const& name, ContextType const& context) {
			// TODO: Serialize context
			_events[name].emit("context");
		}

		bool isRunning() const;

	protected:
		void previousScene();

	private:
		static EntityId _lastSpawnedEntityId;

		std::unordered_map<std::string, EventHandler> _eventHandlers;
		std::unordered_map<std::string, Event<std::string>> _events;
		EntityModels _models;
		Entities _entities;
		bool _running;
	};
}
