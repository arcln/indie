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
		using Roots = std::map<EntityId, Entity>;
		using Childs = std::multimap<EntityId, Entity>;

		void add(Entity const& entity);
		void add(Entity const&& entity);
		Roots const& getRoots() const;
		Childs::iterator getChilds(EntityId id);
		void remove(EntityId id);
	private:
		Roots _roots;
		Childs _childs;
	};
}
