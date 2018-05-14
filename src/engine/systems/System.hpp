/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include <vector>
#include <map>
#include <engine/core/Entity.hpp>
#include <engine/components/ComponentPool.hpp>

namespace engine {

	class System {
	public:
		virtual ~System() = default;

		virtual void update(Entities const& entities) = 0;
	};
}
