/*
** EPITECH PROJECT, 2018
** ECS Engine
** File description:
** Thomas Arbona
*/
#pragma once

#include <functional>
#include <irrlicht/irrlicht.h>
#include "engine/components/ComponentConstraint.hpp"
#include "engine/core/Entity.hpp"

namespace engine {

	struct ItemComponent {
        using Constraint = ComponentConstraint<ItemComponent, false>;
        using UseFunction = std::function<void()>;

        ItemComponent() : use([]() -> void {}) {}
        ItemComponent(UseFunction _use) : use(_use) {}

        UseFunction use;
        irr::core::vector3df offset{0.f, 0.f, 0.f};
	};
}
