/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include <cstddef>
#include <engine/core/Event.hpp>
#include <engine/core/EntityId.hpp>
#include <engine/components/ComponentConstraint.hpp>
#include <engine/components/ComponentFilter.hpp>

namespace engine {

	class Entities;

	template<typename... ComponentsTypes>
	struct Callback {
		using Get = std::function<void(class Entity const&, ComponentsTypes&...)>;
	};

	/**
	 * An entity composed of components. The smallest logic unit in a game
	 */
	class Entity {
	public:
		Entity();
		Entity(EntityId id, EntityId parentId, Entities* entities);
		Entity(Entity const& entity);
		Entity& operator=(Entity const&);
		virtual ~Entity();

		/**
		 * Remove the entity
		 */
		void kill();

		/**
		 * Attach a child to the entity
		 * @param child Entity to become child
		 */
		void attach(Entity const& child);

		/**
		 * Detach the entity from its parent
		 */
		void detach();

		/**
		 * Set a component on the entity. Add a new one if the component is multiple, set it or throw if it isn't
		 * @tparam ComponentType Type of the component to set
		 * @tparam CtorArgsTypes Types of the component ctor's parameters
		 * @param ctorArgs Arguments for the component's ctor
		 */
		template <typename ComponentType, typename... CtorArgsTypes>
		ComponentType&
		set(CtorArgsTypes... ctorArgs) const
		{
			return ComponentSFilter<ComponentType, CtorArgsTypes...>().set(_id, ctorArgs...);
		}

		/**
		 * Get entity's components through a callback
		 * @tparam ComponentsTypes Types of components to get
		 * @param callback Callback taking one argument by ComponentsTypes. Arguments can be component or list of component, depending on the component's ComponentConstraint
		 */
		template<typename... ComponentsTypes>
		void
		get(typename ComponentFilter<ComponentsTypes...>::Callback const& callback) const
		{
			ComponentFilter<ComponentsTypes...>().get(_id, callback);
		}

		EntityId getId() const;

		EntityId getParentId() const;

		static EntityId const nullId;

	private:
		EntityId _id;
		EntityId _parentId;

		Entities* _entities;

	};
}
