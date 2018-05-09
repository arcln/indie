/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include <vector>
#include <map>
#include "../components/Component.hpp"
#include "../core/Entity.hpp"

namespace engine {

	class System {
	public:
		virtual ~System();

		virtual void update(std::vector<std::map<EntityId, Component>&> entities) = 0;

		virtual std::vector<ComponentType> getType() = 0;
	};
}
