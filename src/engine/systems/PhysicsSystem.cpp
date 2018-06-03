/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/
#include <deque>
#include <algorithm>
#include <boost/geometry.hpp>
#include "engine/core/Game.hpp"
#include "PhysicsSystem.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/HitboxComponent.hpp"
#include "../components/PhysicsComponent.hpp"
#include "../helpers/GeometryHelper.hpp"

const engine::Vec2D engine::PhysicsSystem::gravity{0., -480.};
const float engine::PhysicsSystem::tick = 1./60.;

void
engine::PhysicsSystem::update(Entities const& entities)
{
    entities.each<PhysicsComponent, TransformComponent>([&](auto const& e, auto& p, auto& t) {
        engine::Vec2D pos2D(t.position.X, t.position.Y);
        engine::Vec2D newPos2D;

        // apply gravity
        p.velocity += engine::PhysicsSystem::gravity * engine::PhysicsSystem::tick;
        newPos2D = pos2D + p.velocity * engine::PhysicsSystem::tick;
        t.prevPosition = t.position;
        t.position.X = newPos2D.X;
        t.position.Y = newPos2D.Y;

        PhysicsSystem::applyCollision(entities, e);
    });
}

void
engine::PhysicsSystem::applyCollision(Entities const& entities, Entity const& entity)
{
    if (!entity.has<HitboxComponent>())
        return;

    entity.get<PhysicsComponent, HitboxComponent, TransformComponent>([&](auto& p, auto& h, auto& t) {
        h.hitboxW2D = GeometryHelper::transformPolygon(t, h.hitbox2D);

        entities.each<HitboxComponent, TransformComponent>([&](auto const& e2, auto& h2, auto& t2) {
            if (e2.getId() == entity.getId())
                return;

            h2.hitboxW2D = GeometryHelper::transformPolygon(t2, h2.hitbox2D);

            Manifold mf = GeometryHelper::polygonCollide(entity, h, h2);
            if (mf.isCollide) {
                if (mf.hasError) {
                    t.position = t.prevPosition;
                    p.velocity *= 0.f;
                    return;
                }
                p.velocity -= 2 * (p.velocity.dotProduct(mf.normal)) * mf.normal;
                std::cout << mf.normal.X << ", " << mf.normal.Y << std::endl;
                p.velocity *= 0.3; // TODO: rebound velocity
                PhysicsSystem::patchPosition(entity, h2);
                return;
            }
        });
    });
}

void
engine::PhysicsSystem::patchPosition(Entity const& entity, HitboxComponent const& collideWith)
{
    auto& t = entity.get<TransformComponent>();
    auto& h = entity.get<HitboxComponent>();
    auto& p = entity.get<PhysicsComponent>();
    auto bound1 = t.prevPosition;
    auto bound2 = t.position;
    auto cursor = (bound1 + bound2) / 2;

    t.position = bound1;
    h.hitboxW2D = GeometryHelper::transformPolygon(t, h.hitbox2D);
    if (GeometryHelper::simplePolygonCollide(h, collideWith)) {
        std::cout << "aieeeee" << std::endl;
    }

    for (auto it = 0; it < 10; it += 1) {
        t.position = cursor;
        h.hitboxW2D = GeometryHelper::transformPolygon(t, h.hitbox2D);
        if (GeometryHelper::simplePolygonCollide(h, collideWith)) {
            bound2 = cursor;
        } else {
            bound1 = cursor;
        }
        cursor = (bound1 + bound2) / 2;
    }

    float dist = std::fabs(std::sqrt(std::pow(t.position.X - bound1.X, 2) + std::pow(t.position.Y - bound1.Y, 2)));
    auto v = p.velocity;
    v *= engine::PhysicsSystem::tick;
    // std::cout << dist << std::endl;
    t.position = bound1;
    t.position.X += v.X;
    t.position.Y += v.Y;
}
