/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <engine/utils/ComponentConstraint.hpp>

namespace engine {

	struct TimeoutComponent {
		using Constraint = ComponentConstraint<TimeoutComponent, true>;

		TimeoutComponent();
		TimeoutComponent(float after, std::function<void ()> const& callback, bool interval = false);

		float interval;
		float remaining;
		bool done;
		std::function<void ()> callback;
	};
}