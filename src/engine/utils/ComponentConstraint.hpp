/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <functional>
#include "engine/core/ComponentPool.hpp"
#include "engine/core/UniqueComponentPool.hpp"

namespace engine {

	template<typename ComponentType, bool isMultiple>
	struct ComponentConstraint;

	template<typename ComponentType>
	struct ComponentConstraint<ComponentType, true> {
		using Pool = ComponentPool<ComponentType>;
		using ReturnType = typename Pool::Container::mapped_type&;
	};

	template<typename ComponentType>
	struct ComponentConstraint<ComponentType, false> {
		using Pool = UniqueComponentPool<ComponentType>;
		using ReturnType = typename Pool::Container::mapped_type&;
	};

}
