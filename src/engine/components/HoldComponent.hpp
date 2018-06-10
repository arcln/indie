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

        HoldComponent() : items(3) {}
        HoldComponent(std::size_t _capacity) : items(_capacity) {}

        std::size_t count = 0;
        int current = -1;
        std::vector<Entity> items;
        Entity reachableEntity;
        bool hasReachableEntity = false;
	};
}
