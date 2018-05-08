/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include <cstddef>
#include "Component.hpp"

namespace engine {

	using EntityId = std::size_t;

	class Entity {
	public:
		Entity();
		virtual ~Entity();

		void addComponent(Component& component) const;

		size_t get_id() const;

	private:
		static EntityId _nextId = 0;
		EntityId _id;
	};
}
