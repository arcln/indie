/*
** EPITECH PROJECT, 2018
** ECS Engine
** File description:
** Thomas Arbona
*/
#pragma once

#include <irrlicht/irrlicht.h>
#include "engine/utils/ComponentConstraint.hpp"
#include "engine/core/Entity.hpp"

namespace engine {

	struct HoldComponent {
        using Constraint = ComponentConstraint<HoldComponent, false>;

        HoldComponent() : capacity(3) {}
        HoldComponent(std::size_t _capacity) : capacity(_capacity) {}

        std::size_t capacity;
        std::vector<Entity> items;
        Entity reachableEntity;
        bool hasReachableEntity = false;
	};
}
