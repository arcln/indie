/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <irrlicht/irrTypes.h>
#include "engine/utils/ComponentConstraint.hpp"

namespace engine {

	struct AnimationBoundaries {
		AnimationBoundaries() = default;
		AnimationBoundaries(irr::s32 from, irr::s32 length) : from(from), to(from + length - 1) {}
		irr::s32 from;
		irr::s32 to;
	};

	struct AnimationComponent {
		AnimationComponent(std::string const& initalState, irr::f32 frameRate = 60)
			: currentState(initalState)
			, nextState("")
			, playOnce(false)
			, frameRate(frameRate) {}

		using Constraint = ComponentConstraint<AnimationComponent, false>;

		std::unordered_map<std::string, AnimationBoundaries> states;
		std::string currentState;
		std::string nextState;
		bool playOnce;
		irr::f32 frameRate;
	};
}
