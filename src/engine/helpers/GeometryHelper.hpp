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

    struct TransformComponent;
    struct HitboxComponent;
    struct PhysicsComponent;
    class Entity;

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
        bool hasError = false;
        Vec2D normal{0.f, 0.f};
    };

	class GeometryHelper {
	public:
        static std::vector<Segment> getCombinedSegments(Polygon const& p1, Polygon const& p2);
        static bool segmentsAreCollinear(Segment const& s1, Segment const& s2);
        static void transformHitbox(HitboxComponent& hitbox, TransformComponent const& transform);
        static Manifold polygonCollide(Entity const& entity, HitboxComponent& h1, HitboxComponent const& h2, int call = 0);
        static bool simplePolygonCollide(HitboxComponent& h1, HitboxComponent const& h2);
        static Point mergeSegmentsIntoVector(std::vector<Segment> const& segments);
        static bool AABBCollide(HitboxComponent const& h1, HitboxComponent const& h2);

        static const float epsilon;

	private:
        GeometryHelper() = default;
        ~GeometryHelper() = default;
	};
}
