/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/
#include <cmath>
#include "../components/HitboxComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "GeometryHelper.hpp"

const float engine::GeometryHelper::epsilon = 0.000001;

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

    float ABslop = (y2 - y1) / (x2 - x1);
    float BCslop = (y3 - y2) / (x3 - x2);
    float CDslop = (y4 - y3) / (x4 - x3);

    return std::fabs(ABslop - BCslop) < GeometryHelper::epsilon &&
            std::fabs(BCslop - CDslop) < GeometryHelper::epsilon;
}

engine::Manifold
engine::GeometryHelper::polygonCollide(HitboxComponent const& h1, HitboxComponent const& h2)
{
    // TODO: optimize by testing first with AABB collision
    std::deque<Polygon> inter;
    Manifold mf;

    boost::geometry::intersection(h1.hitboxW2D, h2.hitboxW2D, inter);

    mf.isCollide = !inter.empty();
    if (mf.isCollide)
        std::cout << mf.isCollide << std::endl;

    if (mf.isCollide) {
        auto segments = GeometryHelper::getCombinedSegments(inter[0], h2.hitboxW2D);
        Point p1(0.f, 0.f);
        Point p2(0.f, 0.f);

        if (segments.empty()) {
            std::cout << "aie" << std::endl;
            mf.isCollide = false;
            return mf;
        }

        for (auto& segment : segments) {
            p1.x(p1.x() + boost::geometry::get<0, 0>(segment));
            p1.y(p1.y() + boost::geometry::get<0, 1>(segment));
            p2.x(p2.x() + boost::geometry::get<1, 0>(segment));
            p2.y(p2.y() + boost::geometry::get<1, 1>(segment));
        }
        p1.x(p1.x() / segments.size());
        p1.y(p1.y() / segments.size());
        p2.x(p2.x() / segments.size());
        p2.y(p2.y() / segments.size());

        // std::cout << p1.x() << "; " << p1.y() << " " << p2.x() << "; " << p2.y() << std::endl;
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

    return out;
}
