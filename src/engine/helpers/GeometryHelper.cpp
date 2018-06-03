/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/
#include <cmath>
#include "../components/HitboxComponent.hpp"
#include "../components/PhysicsComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "../core/Entity.hpp"
#include "GeometryHelper.hpp"

const float engine::GeometryHelper::epsilon = 0.6;

std::vector<engine::Segment>
engine::GeometryHelper::getCombinedSegments(Polygon const& p1, Polygon const& p2)
{
    std::vector<Segment> v;
    std::vector<Segment> out;

    boost::geometry::for_each_segment(p1, [&](Segment const& seg) -> void {
        v.push_back(seg);
    });

    boost::geometry::for_each_segment(p2, [&](Segment const& seg) -> void {
        for (auto& seg2 : v) {
            if (GeometryHelper::segmentsAreCollinear(seg, seg2)) {
                out.push_back(seg);
            }
        }
    });

    return out;
}

bool
engine::GeometryHelper::segmentsAreCollinear(Segment const& s1, Segment const& s2)
{
    float x1 = boost::geometry::get<0, 0>(s1);
    float y1 = boost::geometry::get<0, 1>(s1);
    float x2 = boost::geometry::get<1, 0>(s1);
    float y2 = boost::geometry::get<1, 1>(s1);
    float x3 = boost::geometry::get<0, 0>(s2);
    float y3 = boost::geometry::get<0, 1>(s2);
    float x4 = boost::geometry::get<1, 0>(s2);
    float y4 = boost::geometry::get<1, 1>(s2);

    return std::fabs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) < 0.1 &&
            std::fabs(x1 * (y2 - y4) + x2 * (y4 - y1) + x4 * (y1 - y2)) < 0.1;
}

bool
engine::GeometryHelper::simplePolygonCollide(HitboxComponent& h1, HitboxComponent const& h2)
{
    std::deque<Polygon> inter;

    boost::geometry::intersection(h1.hitboxW2D, h2.hitboxW2D, inter);

    return !inter.empty();
}

engine::Manifold
engine::GeometryHelper::polygonCollide(Entity const& entity, HitboxComponent& h1, HitboxComponent const& h2, int call)
{
    // TODO: optimize by testing first with AABB collision
    std::deque<Polygon> inter;
    Manifold mf;
    //
    // if (call > 20) {
    //     std::cout << "out error" << std::endl;
    //     mf.isCollide = true;
    //     mf.hasError = true;
    //     return mf;
    // }
    // std::cout << "new" << std::endl;
    // std::cout << boost::geometry::wkt(h1.hitboxW2D) << std::endl;

    boost::geometry::intersection(h1.hitboxW2D, h2.hitboxW2D, inter);


    mf.isCollide = !inter.empty();

    if (mf.isCollide) {
        auto segments = GeometryHelper::getCombinedSegments(inter[0], h2.hitboxW2D);
        Point pt1(0.f, 0.f);
        Point pt2(0.f, 0.f);

        if (segments.empty()) {
            std::cout << boost::geometry::wkt(h1.hitboxW2D) << std::endl;
            std::cout << boost::geometry::wkt(h2.hitboxW2D) << std::endl;
            std::cout << boost::geometry::wkt(inter[0]) << std::endl << std::endl;
            auto& t1 = entity.get<TransformComponent>();

            if (call == 0) {
                Vec2D move(t1.prevPosition.X - t1.position.X, t1.prevPosition.Y - t1.position.Y);
                h1.patch = move.normalize();
            }

            std::cout << "patch " << call << ": " << h1.patch.X << ", " << h1.patch.Y << std::endl;

            t1.position.X += h1.patch.X;
            t1.position.Y += h1.patch.Y;

            h1.hitboxW2D = GeometryHelper::transformPolygon(t1, h1.hitbox2D);

            return GeometryHelper::polygonCollide(entity, h1, h2, call + 1);
        }

        std::cout << "find" << std::endl;

        for (auto& segment : segments) {
            pt1.x(pt1.x() + boost::geometry::get<0, 0>(segment));
            pt1.y(pt1.y() + boost::geometry::get<0, 1>(segment));
            pt2.x(pt2.x() + boost::geometry::get<1, 0>(segment));
            pt2.y(pt2.y() + boost::geometry::get<1, 1>(segment));
        }
        pt1.x(pt1.x() / segments.size());
        pt1.y(pt1.y() / segments.size());
        pt2.x(pt2.x() / segments.size());
        pt2.y(pt2.y() / segments.size());

        Point lineVec(pt2.x() - pt1.x(), pt2.y() - pt1.y());
        Point normal1(-lineVec.y(), lineVec.x());
        Point normal2(lineVec.y(), -lineVec.x());

        auto& velocity = entity.get<PhysicsComponent>().velocity;
        float dot = normal1.x() * velocity.X + normal1.y() * velocity.Y;

        mf.normal.X = dot < 0 ? normal1.x() : normal2.x();
        mf.normal.Y = dot < 0 ? normal1.y() : normal2.y();
        mf.normal.normalize();
    } else {
        std::cout << "no collide: " << boost::geometry::wkt(h1.hitboxW2D) << std::endl;
    }

    return mf;
}

engine::Polygon
engine::GeometryHelper::transformPolygon(TransformComponent const& transform, Polygon const& polygon)
{
    Polygon out;

    boost::geometry::for_each_point(polygon, [&](Point const& p) -> void {
        out.outer().push_back(Point(
            boost::geometry::get<0>(p) * transform.scale.X + transform.position.X,
            boost::geometry::get<1>(p) * transform.scale.Y + transform.position.Y
        ));
    });

    boost::geometry::correct(out);
    return out;
}
