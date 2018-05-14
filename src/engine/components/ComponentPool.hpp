/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <typeindex>
#include <unordered_map>
#include "engine/components/TestComponent.hpp"
#include "engine/components/DisplayComponent.hpp"

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
	using ComponentContainer = std::multimap<EntityId, ComponentType>;

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
		 * @param entityId Entity's id
		 * @return the component
		 */
		ComponentType&
		addComponent(EntityId entityId)
		{
			typename Container::iterator componentIt = _components.emplace(entityId, ComponentType());

			if (componentIt == std::end(_components))
				throw std::runtime_error("unable to add a new component");
			return componentIt->second;
		}

		/**
		 * Get a component by entity id
		 * @param entityId Entity's id
		 * @return the component
		 */
		typename Container::iterator getComponents(EntityId entityId)
		{
			return _components.find(entityId);
		}

		/**
		 * Singleton getter
		 * @return the component pool singleton itself
		 */
		static ComponentPool<ComponentType>& instance() {
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
