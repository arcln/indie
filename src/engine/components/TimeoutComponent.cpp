/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include "TimeoutComponent.hpp"

engine::TimeoutComponent::TimeoutComponent()
{}

engine::TimeoutComponent::TimeoutComponent(float after, std::function<void()> const& callback, bool interval)
	: done(false), callback(callback)
{
	this->remaining = after;

	if (interval) {
		this->interval = after;
	} else {
		this->interval = -1;
	}
}
