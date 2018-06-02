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
    entity.get<PhysicsComponent, HitboxComponent, TransformComponent>([&](auto& p, auto& h, auto& t) {
        h.hitboxW2D = GeometryHelper::transformPolygon(t, h.hitbox2D);

        entities.each<HitboxComponent, TransformComponent>([&](auto const& e2, auto& h2, auto& t2) {
            if (e2.getId() == entity.getId())
                return;

            h2.hitboxW2D = GeometryHelper::transformPolygon(t2, h2.hitbox2D);

            Manifold mf = GeometryHelper::polygonCollide(p, h, h2);
            if (mf.isCollide) {
                std::cout << mf.normal.X << ", " << mf.normal.Y << std::endl;
                t.position = t.prevPosition;
                p.velocity = p.velocity - 2 * (p.velocity.dotProduct(mf.normal)) * mf.normal;
            }
        });
    });
}
