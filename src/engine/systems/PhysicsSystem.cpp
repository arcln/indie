/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/
#include <deque>
#include <chrono>
#include <algorithm>
#include <boost/geometry.hpp>
#include "engine/core/Game.hpp"
#include "PhysicsSystem.hpp"
#include "../Engine.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/HitboxComponent.hpp"
#include "../components/PhysicsComponent.hpp"
#include "../components/HoldComponent.hpp"
#include "../components/ItemComponent.hpp"
#include "../components/TagComponent.hpp"
#include "../helpers/GeometryHelper.hpp"

const engine::Vec2D engine::PhysicsSystem::gravity{0., -400.};

void
engine::PhysicsSystem::update(Scene& scene)
{
    Entities& entities = scene.getEntities();
    auto now = std::chrono::system_clock::now();
    _tick = std::chrono::duration_cast<std::chrono::milliseconds>(now - _prevUpdate).count() / 1000.f;
    _prevUpdate = now;

    if (_tick > 0.5f) {
        return;
    }

    entities.each<PhysicsComponent, TransformComponent>([&](Entity const& e, auto& p, auto& t) {
        engine::Vec2D pos2D(t.position.X, t.position.Y);
        engine::Vec2D newPos2D;

        if (e.has<HoldComponent>()) {
            e.get<HoldComponent>().hasReachableEntity = false;
        }

        if (e.has<ItemComponent>() && p.isGrounded)
            return;

        p.velocity += engine::PhysicsSystem::gravity * _tick;
        newPos2D = pos2D + p.velocity * _tick;
        t.prevPosition = t.position;
        t.position.X = newPos2D.X;
        t.position.Y = newPos2D.Y;

        if (t.position.Y > t.prevPosition.Y) {
            p.isGrounded = false;
        }

        this->applyCollision(entities, e);
        this->applyDeplacement(entities, e);

        if (t.position.Y < -50.f) {
            e.kill();
        }

        p.isGrounded = PhysicsSystem::isGrounded(entities, e);
    }, false);
}

void
engine::PhysicsSystem::applyCollision(Entities& entities, Entity const& entity)
{
    if (!entity.has<HitboxComponent>())
        return;

    entity.get<PhysicsComponent, HitboxComponent, TransformComponent>([&](auto& p, auto& h, auto& t) {
        Manifold mf;
        float rebound = 1.f;
        float dist = std::sqrt(std::pow(t.position.X - t.prevPosition.X, 2) + std::pow(t.position.Y - t.prevPosition.Y, 2));
        std::size_t count = 0;

        if (dist > 2.f) {
            return this->applyCollisionFrac(entities, entity, dist);
        }

        GeometryHelper::transformHitbox(h, t);

        entities.each<HitboxComponent, TransformComponent>([&](Entity const& e2, auto& h2, auto& t2) {
            if (e2.getId() == entity.getId() || count >= PhysicsCollideMaxObj)
                return;

            GeometryHelper::transformHitbox(h2, t2);

            Manifold mf2 = GeometryHelper::polygonCollide(entity, e2, rebound * h2.rebound);
            if (mf2.isCollide && !mf2.hasError) {
                if (h.onCollide) {
                    h.onCollide(e2);
                } else if (h2.onCollide) {
                    h2.onCollide(entity);
                }
                if (e2.has<ItemComponent>()) {
                    if (entity.has<HoldComponent>()) {
                        auto& hc = entity.get<HoldComponent>();
                        hc.hasReachableEntity = true;
                        hc.reachableEntity = e2;
                    }
                } else {
                    count += 1;
                    mf.isCollide = true;
                    mf.normal += mf2.normal;
                    rebound *= h2.rebound;
                }
            }
        }, false);

        if (mf.isCollide) {
            mf.normal.normalize();
            p.velocity -= 2 * (p.velocity.dotProduct(mf.normal)) * mf.normal;
            p.velocity *= h.rebound * rebound;
            PhysicsSystem::patchCollision(entities, entity);
        }
    });
}

void
engine::PhysicsSystem::applyCollisionFrac(Entities& entities, Entity const& entity, float dist)
{
    entity.get<PhysicsComponent, HitboxComponent, TransformComponent>([&](auto& p, auto& h, auto& t) {
        float traveled = 0.f;
        irr::core::vector3df pPrevPosition;

        auto tSave = t;
        auto _p = p;

        _p.velocity.normalize();
        t.position = t.prevPosition;

        while (std::fabs(traveled) <= std::fabs(dist)) {

            pPrevPosition = t.prevPosition;
            t.prevPosition = t.position;
            t.position.X += _p.velocity.X;
            t.position.Y += _p.velocity.Y;
            traveled += 1.f;

            GeometryHelper::transformHitbox(h, t);

            entities.each<HitboxComponent, TransformComponent>([&](auto const& e2, auto& h2, auto& t2) {
                if (e2.getId() == entity.getId())
                    return;

                GeometryHelper::transformHitbox(h2, t2);

                Manifold mf = GeometryHelper::polygonCollide(entity, e2, 0);
                if (mf.isCollide && !mf.hasError) {
                    if (h.onCollide) {
                        h.onCollide(e2);
                    } else if (h2.onCollide) {
                        h2.onCollide(entity);
                    }
                    t.prevPosition = tSave.prevPosition;
                    p.velocity *= 0.f;
                    PhysicsSystem::patchCollisionFrac(entity, e2);
                }
            }, false);
        }
    });
}

void
engine::PhysicsSystem::patchCollision(Entities& entities, Entity const& entity)
{
    auto& t = entity.get<TransformComponent>();
    auto& h = entity.get<HitboxComponent>();
    auto& p = entity.get<PhysicsComponent>();
    auto bound1 = t.prevPosition;
    auto bound2 = t.position;
    auto cursor = (bound1 + bound2) / 2;

    for (auto it = 0; it < 10; it += 1) {
        t.position = cursor;
        GeometryHelper::transformHitbox(h, t);
        if (PhysicsSystem::simpleCollideEntities(entities, entity)) {
            bound2 = cursor;
        } else {
            bound1 = cursor;
        }
        cursor = (bound1 + bound2) / 2;
    }

    float dist = std::fabs(std::sqrt(std::pow(t.position.X - bound1.X, 2) + std::pow(t.position.Y - bound1.Y, 2)));
    auto v = p.velocity;
    v.normalize();
    v *= dist;
    t.position = bound1;
    t.position.X += v.X;
    t.position.Y += v.Y;
}

void
engine::PhysicsSystem::patchCollisionFrac(Entity const& entity, Entity const& entity2)
{
    auto& t = entity.get<TransformComponent>();
    auto& h = entity.get<HitboxComponent>();
    auto bound1 = t.prevPosition;
    auto bound2 = t.position;
    auto cursor = (bound1 + bound2) / 2;

    for (auto it = 0; it < 10; it += 1) {
        t.position = cursor;
        GeometryHelper::transformHitbox(h, t);
        if (GeometryHelper::simplePolygonCollide(entity, entity2)) {
            bound2 = cursor;
        } else {
            bound1 = cursor;
        }
        cursor = (bound1 + bound2) / 2;
    }

    t.position = bound1;
}

void
engine::PhysicsSystem::applyDeplacement(Entities& entities, Entity const& entity)
{
    entity.get<PhysicsComponent, HitboxComponent, TransformComponent>([&](auto& p, auto& h, auto& t) {
        if (p.move.X == 0.f && p.move.Y == 0.f)
            return;

        Manifold gmf;
        std::size_t count = 0;
        auto origin = t.position;
        t.prevPosition = t.position;
        t.position.X += p.move.X * _tick;
        t.position.Y += p.move.Y * _tick;
        GeometryHelper::transformHitbox(h, t);

        entities.each<HitboxComponent, TransformComponent>([&](Entity const& e2, auto& h2, auto& t2) {
            if (e2.getId() == entity.getId() || count >= PhysicsCollideMaxObj)
                return;

            Manifold mf = GeometryHelper::polygonCollide(entity, e2, 0);
            if (mf.isCollide && !mf.hasError) {
                if (e2.has<ItemComponent>()) {
                    if (entity.has<HoldComponent>()) {
                        auto& hc = entity.get<HoldComponent>();
                        hc.hasReachableEntity = true;
                        hc.reachableEntity = e2;
                    }
                } else {
                    gmf.isCollide = true;
                }
            }
        }, false);

        if (gmf.isCollide) {
            t.position = t.prevPosition;
            if (p.isGrounded) {
                p.velocity.Y += 30.f;
            }
        }
        PhysicsSystem::patchDeplacement(entities, entity, origin);
    });
}

void
engine::PhysicsSystem::patchDeplacement(Entities& entities, Entity const& entity, irr::core::vector3df const& origin)
{
    entities.withTag("map", [&](Entity const& entMap) {
        auto& t = entity.get<TransformComponent>();
        auto& h = entity.get<HitboxComponent>();

        t.prevPosition = t.position;
        t.position = origin;
        t.position.Y -= 0.01;
        GeometryHelper::transformHitbox(h, t);
        t.position = t.prevPosition;
        if (!GeometryHelper::simplePolygonCollide(entity, entMap))
            return;

        auto prevPos = t.position;
        bool isOk = false;
        for (auto it = 0; it < 50; it += 1) {
            t.prevPosition = t.position;
            t.position.Y -= 0.02;
            GeometryHelper::transformHitbox(h, t);
            if (GeometryHelper::simplePolygonCollide(entity, entMap)) {
                isOk = true;
                t.position = t.prevPosition;
                break;
            }
        }
        if (!isOk)
            t.position = prevPos;
    });
}

bool
engine::PhysicsSystem::simpleCollideEntities(Entities& entities, Entity const& entity)
{
    if (!entity.has<HitboxComponent>())
        return false;
    bool isCollide = false;

    entity.get<PhysicsComponent, HitboxComponent, TransformComponent>([&](auto& p, auto& h, auto& t) {
        GeometryHelper::transformHitbox(h, t);

        entities.each<HitboxComponent, TransformComponent>([&](Entity const& e2, auto& h2, auto& t2) {
            if (e2.getId() == entity.getId() || e2.has<ItemComponent>() || isCollide)
                return;

            if (GeometryHelper::simplePolygonCollide(entity, e2))
                isCollide = true;
        }, false);
    });

    return isCollide;
}

bool
engine::PhysicsSystem::isGrounded(Entities& entities, Entity const& entity)
{
    bool isGrounded = false;

    entities.withTag("map", [&](Entity const& entMap) {
        if (isGrounded)
            return;

        auto& t = entity.get<TransformComponent>();
        auto& h = entity.get<HitboxComponent>();

        t.prevPosition = t.position;
        t.position.Y -= 0.5f;
        GeometryHelper::transformHitbox(h, t);
        t.position = t.prevPosition;
        isGrounded = GeometryHelper::simplePolygonCollide(entity, entMap);
    });

    return isGrounded;
}
