/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/
#pragma once

#include <vector>
#include <irrlicht/irrlicht.h>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

namespace engine {

    class TransformComponent;
    class HitboxComponent;
    class PhysicsComponent;

    using Point = boost::geometry::model::d2::point_xy<float>;
    using Polygon = boost::geometry::model::polygon<Point>;
    using Segment = boost::geometry::model::referring_segment<const Point>;

    using Vec2D = irr::core::vector2d<float>;

    struct Segment3D {
        irr::core::vector3df p1;
        irr::core::vector3df p2;
    };


    struct Manifold {
        bool isCollide = false;
        Vec2D normal{-1.f, -1.f};
    };

	class GeometryHelper {
	public:
        static std::vector<Segment> getCombinedSegments(Polygon const& p1, Polygon const& p2);
        static bool segmentsAreCollinear(Segment const& s1, Segment const& s2);
        static Polygon transformPolygon(TransformComponent const& transform, Polygon const& polygon);
        static Manifold polygonCollide(PhysicsComponent const& p1, HitboxComponent const& h1, HitboxComponent const& h2);

        static const float epsilon;

	private:
        GeometryHelper() = default;
        ~GeometryHelper() = default;
	};
}
