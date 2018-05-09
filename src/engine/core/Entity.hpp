/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include <cstddef>
#include <vector>
#include "../components/Component.hpp"

namespace engine {

	using EntityId = std::size_t;

	class Entity {
	public:
		Entity();
		virtual ~Entity();

		void addComponent(Component& component) const;

		template <typename ComponentType>
		ComponentType const& getComponent() const
		{
		}

		template <typename ComponentType>
		std::vector<ComponentType const*> getComponents() const
		{
		}

		size_t getId() const;

		static EntityId _nextId;
	private:
		EntityId _id;
	};
}
