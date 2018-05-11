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

	template <typename ComponentType>
	using ComponentContainer = std::multimap<EntityId, ComponentType>;

	template <typename ComponentType>
	using UniqueComponentContainer = std::map<EntityId, ComponentType>;

	/**
	 * Singleton that contains all the components of a type
	 * @tparam ContainerType Type of the container used to store the components, can be either ComponentContainer or UniqueComponentContainer
	 * @tparam ComponentType Type of the components handled by the pool, can be anything
	 */
	template <typename ContainerType, typename ComponentType>
	class ComponentPool {
	public:
		using Components = ContainerType;

		ComponentPool(ComponentPool const&) = delete;
		ComponentPool(ComponentPool&&) = delete;
		ComponentPool& operator=(ComponentPool const&) = delete;
		ComponentPool& operator=(ComponentPool &&) = delete;

		/**
		 * Copy all component from an entity to another
		 * @param dest Entity destination
		 * @param src Entity source
		 */
		void copyComponents(EntityId dest, EntityId src);

		/**
		 * Remove all components of an entity by its id
		 * @param entityId Entity's id to remove
		 */
		void removeComponents(EntityId entityId);

		ComponentType&
		addComponent(EntityId entityId)
		{
			typename Components::iterator componentIt = _components.emplace(entityId, ComponentType());

			if (componentIt == std::end(_components))
				throw std::runtime_error("unable to add a new component");
			return componentIt->second;
		}

		ComponentType&
		getComponent(EntityId entityId)
		{
			typename Components::iterator componentIt = _components.find(entityId);

			if (componentIt == std::end(_components))
				throw std::runtime_error("component not found");
			return componentIt->second;

		}

		typename Components::iterator
		getComponents(EntityId entityId)
		{
			return _components.find(entityId);
		}

		/**
		 * Singleton getter
		 * @return the component pool singleton itself
		 */
		static ComponentPool& instance() {
			static ComponentPool componentPool;

			return componentPool;
		}

	private:
		Components _components;

		ComponentPool() = default;
	};
}
