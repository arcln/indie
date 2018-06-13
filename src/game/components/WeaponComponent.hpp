/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/

#pragma once

#include "engine/utils/ComponentConstraint.hpp"
#include "engine/helpers/GeometryHelper.hpp"

namespace worms {

	struct WeaponComponent {
		using Constraint = engine::ComponentConstraint<WeaponComponent, false>;

        bool hasAim = false;
        engine::Vec2D aimPosition{0.f, 0.f};
        engine::Vec2D aimWPosition{0.f, 0.f};
	};
}
