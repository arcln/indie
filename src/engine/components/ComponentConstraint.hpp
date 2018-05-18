/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <functional>
#include "engine/components/ComponentPool.hpp"
#include "engine/components/UniqueComponentPool.hpp"

namespace engine {

	template<typename ComponentType, bool isMultiple>
	struct ComponentConstraint;

	template<typename ComponentType>
	struct ComponentConstraint<ComponentType, true> {
		using Pool = ComponentPool<ComponentType>;
		using Type = ComponentType;
		using ReturnType = typename Pool::Container::iterator;
	};

	template<typename ComponentType>
	struct ComponentConstraint<ComponentType, false> {
		using Pool = UniqueComponentPool<ComponentType>;
		using Type = ComponentType;
		using ReturnType = ComponentType&;
	};

}
