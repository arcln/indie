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
#include <engine/components/ComponentPool.hpp>

namespace engine {

	using Entities = std::multimap<EntityId, class Entity>;

	/**
	 * An entity composed of components. The smallest logic unit in a game
	 */
	class Entity {
	public:
		Entity();
		Entity(EntityId id, EntityId parentId, Entities* entities);
		Entity(Entity const& entity);
		Entity& operator=(Entity const& entity);
		virtual ~Entity();

		void kill();

		template <typename ComponentType>
		ComponentType&
		addComponent() const
		{
			return ComponentPool<engine::ComponentContainer<ComponentType>, ComponentType>::instance().addComponent(_id);
		}

		template <typename ComponentType>
		ComponentType&
		getComponent() const
		{
			return ComponentPool<engine::UniqueComponentContainer<ComponentType>, ComponentType>::instance().getComponent(_id);
		}

		template <typename ComponentType>
		typename engine::ComponentContainer<ComponentType>::iterator
		getComponents() const
		{
			return ComponentPool<engine::ComponentContainer<ComponentType>, ComponentType>::instance().getComponents(_id);
		}

		size_t getId() const;

		static EntityId const nullId;

	private:
		EntityId _id;
		EntityId _parentId;

		Entities* _entities;
	};
}
