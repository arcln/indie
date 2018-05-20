/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include "engine/core/Entity.hpp"

namespace engine {

	/**
	 * Compare two Entitys by their ids
	 */
	class EntityComparator {
	public:
		explicit EntityComparator(Entity const& entity);

		bool operator()(Entity const& entity) const;

	private:
		EntityId _leftId;
	};
}


