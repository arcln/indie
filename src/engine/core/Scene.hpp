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

		using EntityModels = std::unordered_map<std::string, EntityModel>;
		using Events = std::unordered_map<std::string, Event<GenericEvent>*>;

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
		 * @param parentId Id of the Entity to which the spawned one should be attached
		 * @return the spawned entity
		 */
		Entity const& spawnEntity(std::string const& name, EntityId parentId = Entity::nullId);

		/**
		 * Spawn an entity based on the model designated by its name
		 * @param name Model's name
		 * @param initialisation Function that modify the spawned entity
		 * @param parentId Id of the Entity to which the spawned one should be attached
		 * @return the spawned entity
		 */
		Entity const& spawnEntity(std::string const& name, EntityModel const& initialisation, EntityId parentId = Entity::nullId);

		Entities const& getEntities() const;

		template <typename ContextType>
		void registerEvent(std::string const& name, typename Event<ContextType>::CallbackType const& handler) {
			if (this->events.find(name) == std::end(this->events)) {
				this->events[name] = reinterpret_cast<Event<GenericEvent>*>(::new Event<ContextType>());
			}

			reinterpret_cast<Event<ContextType>*>(this->events[name])->subscribe(handler);
		}

		template <typename ContextType>
		void triggerEvent(std::string const& name, ContextType const& context = ContextType()) {
			if (this->events.find(name) == std::end(this->events)) {
				throw std::runtime_error("event '" + name + "' does not exists");
			}

			reinterpret_cast<Event<ContextType>*>(this->events[name])->emit(context);
		}

		template <typename ContextType>
		void triggerSyncedEvent(std::string const& name, ContextType const& context) {
			this->triggerEvent<ContextType>(name, context);
			this->socket.send<network::TextMessage>(name + "|" + context.serialize());
		}

		void synchonizeWith(std::string const& hostname);

		bool isRunning() const;

		Events events;
		network::ClientSocket socket;

	protected:
		void previousScene();

	private:
		static EntityId _lastSpawnedEntityId;

		EntityModels _models;
		Entities _entities;
		bool _running;
	};
}
