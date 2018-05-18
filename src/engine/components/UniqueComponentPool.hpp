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
#include "engine/core/EntityId.hpp"

namespace engine {

	/**
	 * Container holding components with an 1-1 relation between an entity and themselves
	 * @tparam ComponentType Type of the components handled by the container, can be anything
	 */
	template <typename ComponentType>
	using UniqueComponentContainer = std::map<EntityId, ComponentType>;

	/**
	 * Singleton that contains all unique components of a type
	 * @tparam ComponentType Type of the components handled by the pool, can be anything
	 */
	template <typename ComponentType>
	class UniqueComponentPool {
	public:
		using Container = UniqueComponentContainer<ComponentType>;

		UniqueComponentPool(UniqueComponentPool const&) = delete;
		UniqueComponentPool(UniqueComponentPool&&) = delete;
		UniqueComponentPool& operator=(UniqueComponentPool const&) = delete;
		UniqueComponentPool& operator=(UniqueComponentPool &&) = delete;

		/**
		 * Set a unique component of an entity
		 * @tparam CtorArgsTypes Types of the Component ctor's parameters
		 * @param entityId Entity's id
 		 * @param ctorArgs Component ctor's parameters
		 * @return the component
		 */
		template <typename... CtorArgsTypes>
		ComponentType&
		setComponent(EntityId entityId, CtorArgsTypes... ctorArgs)
		{
			auto const& componentIt = _components.emplace(entityId, ComponentType(std::forward<CtorArgsTypes>(ctorArgs)...));

			if (!componentIt.second)
				throw std::runtime_error("unable to set a new component");
			return componentIt.first->second;
		}

		/**
		 * Check if an entity has a component
		 * @param entityId Entity's id
		 * @return whether the entity has a component or not
		 */
		bool hasComponent(EntityId entityId)
		{
			return (_components.find(entityId) != std::end(_components));
		}

		/**
		 * Get a component by entity id
		 * @param entityId Entity's id
		 * @return the component
		 */
		ComponentType& get(EntityId entityId)
		{
			typename Container::iterator componentIt = _components.find(entityId);

			if (componentIt == std::end(_components))
				throw std::runtime_error("component not found");
			return componentIt->second;

		}

		/**
		 * Singleton getter
		 * @return the component pool singleton itself
		 */
		static UniqueComponentPool& instance() {
			static UniqueComponentPool componentPool;

			return componentPool;
		}

	private:
		Container _components;

		UniqueComponentPool() = default;
	};
}
