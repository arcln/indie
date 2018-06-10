/*
** EPITECH PROJECT, 2018
** Thomas Arbona
** File description:
** engine
*/
#pragma once

#include <irrlicht/irrlicht.h>
#include <vector>
#include <functional>
#include "engine/utils/ComponentConstraint.hpp"
#include "../helpers/GeometryHelper.hpp"

namespace engine {

    class Entity;

	struct HitboxComponent {
		using Constraint = ComponentConstraint<HitboxComponent, false>;
        using OnCollideFunction = std::function<void(Entity const&)>;

		HitboxComponent();
		HitboxComponent(std::string const& polygon);

        std::vector<Segment3D> segments3D;
        float rebound = 0.3;
        Vec2D patch;
        Vec2D size;
        Vec2D WSize;
        Vec2D AABBPosition;
        Vec2D AABBWPosition;
        Polygon hitbox2D;
		Polygon hitboxW2D;
        bool hasDebugMode = false;
        bool isAABBOnly = false;
        bool isStatic = false;
        bool isComputed = false;
        OnCollideFunction onCollide;
	};
}
