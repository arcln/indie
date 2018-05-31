/*
** EPITECH PROJECT, 2018
** Thomas Arbona
** File description:
** engine
*/
#include <vector>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#pragma once

namespace engine {

    struct Segment3D {
        irr::core::vector3df p1;
        irr::core::vector3df p2;
    };

	struct HitboxComponent {
		using Constraint = ComponentConstraint<HitboxComponent, false>;
        using Point = boost::geometry::model::d2::point_xy<float>;
		using Polygon = boost::geometry::model::polygon<Point>;

		HitboxComponent();
		HitboxComponent(std::string const& polygon);

        std::vector<Segment3D> segments3D;
		Polygon hitbox2D;
        bool hasDebugMode;
	};
}
