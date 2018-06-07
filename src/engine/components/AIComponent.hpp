/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <engine/utils/Lua.hpp>
#include "ComponentConstraint.hpp"

namespace engine {

	struct AIComponent {
		AIComponent() = default;
		explicit AIComponent(std::string const& scriptPath) : scriptPath(scriptPath) {}
		using Constraint = ComponentConstraint<AIComponent, false>;

		std::string scriptPath;
	};
}
