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

	/**
	 * An entity composed of components. The smallest logic unit in a game
	 */
	class Entity {
	public:
		Entity();
		explicit Entity(ComponentPool* componentPool);
		Entity(Entity const& entity);
		Entity& operator=(Entity const& entity);
		virtual ~Entity();

		Entity& copyComponents(engine::Entity const& entity);

		template <typename ComponentType>
		ComponentType&
		addComponent() const
		{
			return _componentPool->addComponent<ComponentType>(_id);
		}

		template <typename ComponentType>
		ComponentType&
		getComponent() const
		{
			return _componentPool->getComponent<ComponentType>(_id);
		}

		template <typename ComponentType>
		typename Components<ComponentType>::iterator
		getComponents() const
		{
			return _componentPool->getComponents<ComponentType>(_id);
		}

		size_t getId() const;

		static EntityId _nextId;

	private:
		EntityId _id;
		ComponentPool* _componentPool;
	};
}
