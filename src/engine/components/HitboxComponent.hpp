/*
** EPITECH PROJECT, 2018
** Thomas Arbona
** File description:
** engine
*/
#pragma once

#include <irrlicht/irrlicht.h>
#include <vector>
#include "engine/components/ComponentConstraint.hpp"
#include "../helpers/GeometryHelper.hpp"

namespace engine {

	struct HitboxComponent {
		using Constraint = ComponentConstraint<HitboxComponent, false>;

		HitboxComponent();
		HitboxComponent(std::string const& polygon);

        std::vector<Segment3D> segments3D;
        Vec2D patch;
        Polygon hitbox2D;
		Polygon hitboxW2D;
        bool hasDebugMode;
	};
}
