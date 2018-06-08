/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include "engine/utils/ComponentConstraint.hpp"

namespace engine {

	class TagComponent {
	public:
		using Constraint = ComponentConstraint<TagComponent, true>;

        TagComponent();
		TagComponent(std::string const& tag) : value(tag) {};

		std::string value;
	};
}
