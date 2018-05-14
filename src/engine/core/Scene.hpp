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
#include <memory>
#include "engine/core/Event.hpp"
#include "engine/core/Entity.hpp"
#include "engine/core/Entities.hpp"
#include "engine/network/Message.hpp"
#include "engine/network/Socket.hpp"

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
		using Events = std::unordered_map<std::string, std::shared_ptr<Event<GenericEvent>>>;

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
			this->events[name] = std::make_shared<Event<ContextType>>();
			reinterpret_cast<Event<ContextType>*>(this->events[name].get())
				->subscribe([&](ContextType const& context) -> int {
				// TODO: Deserialize context
				_eventHandlers[name](&context);
				return 0;
			});
		}

		template <typename ContextType>
		void triggerEvent(std::string const& name, ContextType const& context) {
			reinterpret_cast<Event<ContextType>*>(this->events[name].get())->emit(context);
		}

		template <typename ContextType>
		void triggerSyncedEvent(std::string const& name, ContextType const& context) {
			this->triggerEvent(name, context);

			// TODO: Serialize context
			this->socket.send<std::string>(name);
		}

		void synchonizeWith(std::string const& hostname);

		bool isRunning() const;

		Events events;
		network::ClientSocket socket;

	protected:
		void previousScene();

	private:
		static EntityId _lastSpawnedEntityId;

		std::unordered_map<std::string, EventHandler> _eventHandlers;
		EntityModels _models;
		Entities _entities;
		bool _running;
	};
}
