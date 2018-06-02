/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include "ComponentConstraint.hpp"

namespace engine {

	class TagComponent {
	public:
		using Constraint = ComponentConstraint<TagComponent, true>;

		std::string value;
	};
}
