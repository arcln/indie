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
		using ReturnType = const typename Pool::Container::mapped_type&;
	};

	template<typename ComponentType>
	struct ComponentConstraint<ComponentType, false> {
		using Pool = UniqueComponentPool<ComponentType>;
		using ReturnType = typename Pool::Container::mapped_type&;
	};

}
