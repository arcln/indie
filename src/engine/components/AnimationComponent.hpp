/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <irrlicht/irrTypes.h>
#include "engine/components/ComponentConstraint.hpp"

namespace engine {

	struct AnimationBoundaries {
		AnimationBoundaries() = default;
		AnimationBoundaries(irr::s32 from, irr::s32 to) : from(from), to(to) {}
		irr::s32 from;
		irr::s32 to;
	};

	struct AnimationComponent {
		AnimationComponent(std::string const& initalState, irr::f32 frameRate) : currentState(initalState), frameRate(frameRate) {}

		using Constraint = ComponentConstraint<AnimationComponent, false>;

		std::map<std::string, AnimationBoundaries> states;
		std::string currentState;
		irr::f32 frameRate;
	};
}
