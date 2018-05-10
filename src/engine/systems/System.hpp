/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include <vector>
#include <map>
#include <engine/core/EntityId.hpp>
#include <engine/components/ComponentPool.hpp>


#include "engine/components/DisplayComponent.hpp"

namespace engine {

	class System {
	public:
		virtual ~System();

		virtual void update(AnyComponents& entities) = 0;
	};
}
