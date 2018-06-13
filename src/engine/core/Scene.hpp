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
		Entity spawnEntity(std::string const& name, EntityId parentId = Entity::nullId);

		/**
		 * Spawn an entity based on the model designated by its name
		 * @param name Model's name
		 * @param initialisation Function that modify the spawned entity
		 * @param parentId Id of the Entity to which the spawned one should be attached
		 * @return the spawned entity
		 */
		Entity spawnEntity(std::string const& name, EntityModel const& initialisation, EntityId parentId = Entity::nullId);

		Entities& getEntities();

		template <typename ContextType>
		void registerEvent(std::string const& name, EntityId target, typename Event<ContextType>::CallbackType const& handler) {
			if (_events.find(name) == std::end(_events)) {
				_events[name] = reinterpret_cast<Event<GenericEvent>*>(::new Event<ContextType>());
			}

			reinterpret_cast<Event<ContextType>*>(_events[name])->subscribe(handler, target);
		}

		template <typename ContextType>
		void triggerEvent(std::string const& name, EntityId target = 0, ContextType const& context = ContextType()) {
			if (_events.find(name) == std::end(_events)) {
				throw std::runtime_error("event '" + name + "' does not exists");
			}

			reinterpret_cast<Event<ContextType>*>(_events[name])->emit(context, target);
		}

		void triggerSyncedEvent(std::string const& name, EntityId target = 0, std::string const& serializedContext = "") {
			this->triggerEvent<std::string>(name, target, serializedContext);

			if (_synced) {
				_socket.send<network::TextMessage>(name + "|" + serializedContext);
			}
		}

		void deleteEvent(std::string const& evt, EntityId id = Entity::nullId);
		void synchronizeWith(std::string const& hostname, class Game& game);
		bool isRunning() const;
		bool hasEvent(std::string const& evtName) const;
		std::size_t id() const;

	protected:
		void previousScene();

	private:
		static std::size_t _LastSceneId;

		Events _events;
		network::ClientSocket _socket;
		EntityModels _models;
		Entities _entities;
		bool _running;
		bool _synced;
		std::size_t _id;
	};
}
