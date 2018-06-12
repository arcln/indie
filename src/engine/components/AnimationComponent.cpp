/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include "AnimationComponent.hpp"

engine::AnimationBoundaries::AnimationBoundaries(irr::s32 from, irr::s32 length)
	: from(from)
	, to(from + length - 1) {}

engine::AnimationBoundaries
engine::AnimationBoundaries::operator+(irr::s32 offset)
{
	return {
		this->from + offset,
		this->to + offset
	};
}

engine::AnimationComponent::AnimationComponent(std::string const& initalState, irr::f32 frameRate)
	: currentState(initalState)
	, nextState("")
	, playOnce(false)
	, frameRate(frameRate) {}
