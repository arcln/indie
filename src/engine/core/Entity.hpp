/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include <cstddef>
#include <vector>
#include <engine/Event.hpp>
#include <engine/components/ComponentPool.hpp>
#include <engine/core/EntityId.hpp>

namespace engine {

	/**
	 * An entity composed of components. The smallest logic unit in a game
	 */
	class Entity {
	public:
		Entity(ComponentPool& componentPool);
		virtual ~Entity();

		/**
		 * Add a test component
		 * @return Test component added
		 */
		std::shared_ptr<TestComponent> addTestComponent() const;

		std::shared_ptr<TestComponent> getTestComponent() const;

		size_t getId() const;

		static EntityId _nextId;
	private:
		EntityId _id;
		ComponentPool& _componentPool;
	};
}
