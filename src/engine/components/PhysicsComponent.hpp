/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/
#pragma once

#include <irrlicht/irrlicht.h>
#include "engine/components/ComponentConstraint.hpp"


namespace engine {
	using Vec2D = irr::core::vector2d<float>;

	struct PhysicsComponent {
        using Constraint = ComponentConstraint<PhysicsComponent, false>;
        Vec2D velocity{0., 0.};
	};
}
