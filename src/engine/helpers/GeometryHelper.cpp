/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/
#include <cmath>
#include "../Engine.hpp"
#include "../components/HitboxComponent.hpp"
#include "../components/PhysicsComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "../core/Entity.hpp"
#include "../core/Entities.hpp"
#include "GeometryHelper.hpp"

const float engine::GeometryHelper::epsilon = 0.01;

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
            if (GeometryHelper::segmentsAreCollinear(seg, seg2))
                out.push_back(seg);
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

    return std::fabs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) < GeometryHelper::epsilon &&
            std::fabs(x1 * (y2 - y4) + x2 * (y4 - y1) + x4 * (y1 - y2)) < GeometryHelper::epsilon;
}

bool
engine::GeometryHelper::simplePolygonCollide(Entity const& entity, Entity const& entity2)
{
    std::deque<Polygon> inter;
    auto& h1 = entity.get<HitboxComponent>();
    auto& h2 = entity2.get<HitboxComponent>();

    if (!GeometryHelper::AABBCollide(h1, h2))
        return false;

    if (h2.isAABBOnly) {
        bool isCollide = false;
        Entities* entities = entity.getEntities();

        if (!entities)
            return isCollide;

        entities->eachChilds(entity2.getId(), [&](Entity const& child) {
            auto& h3 = child.get<HitboxComponent>();
            boost::geometry::intersection(h1.hitboxW2D, h3.hitboxW2D, inter);
            if (!inter.empty()) {
                isCollide = true;
            }
        }, false);

        return isCollide;
    }

    boost::geometry::intersection(h1.hitboxW2D, h2.hitboxW2D, inter);
    return !inter.empty();
}

bool
engine::GeometryHelper::AABBCollide(HitboxComponent const& h1, HitboxComponent const& h2)
{
    return !((h2.AABBWPosition.X >= h1.AABBWPosition.X + h1.WSize.X)
        || (h2.AABBWPosition.X + h2.WSize.X <= h1.AABBWPosition.X)
        || (h2.AABBWPosition.Y <= h1.AABBWPosition.Y - h1.WSize.Y)
        || (h2.AABBWPosition.Y - h2.WSize.Y >= h1.AABBWPosition.Y));
}

engine::Manifold
engine::GeometryHelper::polygonCollide(Entity const& entity, Entity const& entity2, float rebound, int call)
{
    std::deque<Polygon> inter;
    Manifold mf;
    auto& h1 = entity.get<HitboxComponent>();
    auto& h2 = entity2.get<HitboxComponent>();

    if (call > 42) {
        mf.isCollide = true;
        mf.hasError = true;
        return mf;
    }

    if (call == 0 && !GeometryHelper::AABBCollide(h1, h2))
        return mf;

    if (h2.isAABBOnly) {
        return GeometryHelper::polygonCollideChilds(entity, entity2, rebound);
    }

    boost::geometry::intersection(h1.hitboxW2D, h2.hitboxW2D, inter);
    mf.isCollide = !inter.empty();

    if (mf.isCollide && rebound) {
        auto segments = GeometryHelper::getCombinedSegments(inter[0], h2.hitboxW2D);
        auto& t1 = entity.get<TransformComponent>();

        if (segments.empty()) {
            if (call == 0) {
                Vec2D move(t1.prevPosition.X - t1.position.X, t1.prevPosition.Y - t1.position.Y);
                h1.patch = move.normalize();
            }

            t1.position.X += h1.patch.X;
            t1.position.Y += h1.patch.Y;
            GeometryHelper::transformHitbox(h1, t1);
            return GeometryHelper::polygonCollide(entity, entity2, rebound, call + 1);
        }

        Point lineVec = GeometryHelper::mergeSegmentsIntoVector(segments);
        Point normal1(-lineVec.y(), lineVec.x());
        Point normal2(lineVec.y(), -lineVec.x());
        auto objVec = t1.position - t1.prevPosition;
        float dot = normal1.x() * objVec.X + normal1.y() * objVec.Y;

        mf.normal.X = dot < 0 ? normal1.x() : normal2.x();
        mf.normal.Y = dot < 0 ? normal1.y() : normal2.y();
        mf.normal.normalize();
    }

    return mf;
}

engine::Manifold
engine::GeometryHelper::polygonCollideChilds(Entity const& entity, Entity const& entity2, float rebound)
{
    Manifold mf;
    Entities* entities = entity.getEntities();
    std::size_t count = 0;

    if (!entities)
        return mf;

    entities->eachChilds(entity2.getId(), [&](Entity const& child) {
        if (count >= PhysicsCollideMaxObj)
            return;

        Manifold mf2 = GeometryHelper::polygonCollide(entity, child, rebound);

        if (mf2.isCollide && !mf2.hasError) {
            count += 1;
            mf.isCollide = true;
            mf.normal += mf2.normal;
        }
    }, false);

    return mf;
}

engine::Point
engine::GeometryHelper::mergeSegmentsIntoVector(std::vector<engine::Segment> const& segments)
{
    Point pt1(0.f, 0.f);
    Point pt2(0.f, 0.f);

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
    return lineVec;
}

void
engine::GeometryHelper::transformHitbox(HitboxComponent& hitbox, TransformComponent const& transform)
{
    if (hitbox.isStatic && hitbox.isComputed)
        return;

    Polygon out;

    boost::geometry::for_each_point(hitbox.hitbox2D, [&](Point const& p) -> void {
        out.outer().push_back(Point(
            boost::geometry::get<0>(p) * transform.scale.X + transform.position.X,
            boost::geometry::get<1>(p) * transform.scale.Y + transform.position.Y
        ));
    });

    boost::geometry::correct(out);
    hitbox.hitboxW2D = out;
    hitbox.AABBWPosition.X = (hitbox.AABBPosition.X * transform.scale.X) + transform.position.X;
    hitbox.AABBWPosition.Y = (hitbox.AABBPosition.Y * transform.scale.Y) + transform.position.Y;
    hitbox.WSize.X = (hitbox.size.X * transform.scale.X);
    hitbox.WSize.Y = (hitbox.size.Y * transform.scale.Y);
    hitbox.isComputed = true;
}

engine::Entity
engine::GeometryHelper::createBlastPolygon(engine::Scene& scene, float x, float y, float radius)
{
	float n = 30.f;
	irr::core::vector2df position;
	engine::Entity blastEntity = scene.spawnEntity("hitboxBlast");
	std::string hitbox("( ");

	hitbox += std::to_string(float(x + (radius * cos(2.f * M_PI * 0.f / n)))) + " "
		  + std::to_string(float(y + (radius * sin(2.f * M_PI * 0.f / n))));
	for (float i = 1.f; i < n; i += 1.f) {

		position.X = float(x + (radius * cos(2.f * M_PI * i / n)));
		position.Y = float(y + (radius * sin(2.f * M_PI * i / n)));

		hitbox += ", " + std::to_string(position.X) + " " + std::to_string(position.Y);
	}
	hitbox += ")";
	auto& h = blastEntity.set<engine::HitboxComponent>(hitbox);
	auto& t = blastEntity.get<engine::TransformComponent>();

	h.hasDebugMode = true;
	t.position = {0.f, 0.f, 0.f};
	t.scale = {1.f, 1.f, 1.f};

	return blastEntity;
}
