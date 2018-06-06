/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <iostream>
#include <map>
#include <list>
#include <engine/exceptions/ComponentPoolException.hpp>
#include "engine/core/EntityId.hpp"
#include "engine/core/Event.hpp"

namespace engine {

	namespace internal {

		/**
		 * An event to reset all the component pools by emitting true
		 */
		extern Event<bool, bool> componentPoolReset;
	}

	/**
	 * Container holding components with an 1-N relation between an entity and themselves
	 * @tparam ComponentType Type of the components handled by the container, can be anything
	 */
	template <typename ComponentType>
	using ComponentContainer = std::map<EntityId, std::vector<ComponentType> >;

	/**
	 * Singleton that contains all components of a type
	 * @tparam ComponentType Type of the components handled by the pool, can be anything
	 */
	template <typename ComponentType>
	class ComponentPool {
	public:
		using Container = ComponentContainer<ComponentType>;

		ComponentPool(ComponentPool const&) = delete;
		ComponentPool(ComponentPool&&) = delete;
		ComponentPool& operator=(ComponentPool const&) = delete;
		ComponentPool& operator=(ComponentPool &&) = delete;

		/**
		 * Add a component to an entity
		 * @tparam CtorArgsTypes Types of the Component ctor's parameters
		 * @param entityId Entity's id
		 * @param ctorArgs Component ctor's parameters
		 * @return the component
		 */
		template <typename... CtorArgsTypes>
		ComponentType&
		set(EntityId entityId, CtorArgsTypes... ctorArgs)
		{
			_components[entityId].push_back(std::forward<CtorArgsTypes>(ctorArgs)...);
			return _components[entityId].back();
		}

		/**
		 * Get components by entity id
		 * @param entityId Entity's id
		 * @return Entity's components
		 */
		typename Container::mapped_type
		get(EntityId entityId)
		{
			typename Container::iterator componentIt = _components.find(entityId);

			if (componentIt == std::end(_components))
				throw internal::ComponentPoolException("components not found");
			return componentIt->second;
		}

		/**
		 * Check if an entity has some components
		 * @param entityId Entity's id
		 * @return whether the entity has or not the requested components
		 */
		bool
		has(EntityId entityId)
		{
			return _components.find(entityId) != std::end(_components);
		}

		/**
		 * Singleton getter
		 * @return the component pool singleton itself
		 */
		static ComponentPool<ComponentType>&
		instance() {
			static ComponentPool<ComponentType> componentPool;

			return componentPool;
		}

	private:
		Container _components;

		/**
		 * Constructor. Register to the componentPoolReset event
		 */
		ComponentPool() {
			internal::componentPoolReset.subscribe([&](bool reset) -> int {
				if (reset) {
					_components.clear();
				}
				return reset;
			});
		}
	};
}
