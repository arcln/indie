/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include "Entity.hpp"

namespace engine {

	class Entities {
	public:
		void add(Entity const& entity);
		void add(Entity const&& entity);
		Entity const& get(EntityId id);
		void remove(EntityId id);
	private:
		std::map<EntityId, Entity> _entities;
		std::multimap<EntityId, Entity> _childs;
	};
}
