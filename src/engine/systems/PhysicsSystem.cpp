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
#include "../components/TransformComponent.hpp"
#include "../components/HitboxComponent.hpp"
#include "../components/PhysicsComponent.hpp"
#include "../helpers/GeometryHelper.hpp"

const engine::Vec2D engine::PhysicsSystem::gravity{0., -400.};

// TODO: handle jump properly
void
engine::PhysicsSystem::update(Entities const& entities)
{
    auto now = std::chrono::system_clock::now();
    _tick = std::chrono::duration_cast<std::chrono::milliseconds>(now - _prevUpdate).count() / 1000.f;
    _prevUpdate = now;

    entities.each<PhysicsComponent, TransformComponent>([&](auto const& e, auto& p, auto& t) {
        engine::Vec2D pos2D(t.position.X, t.position.Y);
        engine::Vec2D newPos2D;

        // apply gravity
        p.velocity += engine::PhysicsSystem::gravity * _tick;
        newPos2D = pos2D + p.velocity * _tick;
        t.prevPosition = t.position;
        t.position.X = newPos2D.X;
        t.position.Y = newPos2D.Y;

        PhysicsSystem::applyCollision(entities, e);
        PhysicsSystem::applyDeplacement(entities, e);
    });
}

void
engine::PhysicsSystem::applyCollision(Entities const& entities, Entity const& entity)
{
    if (!entity.has<HitboxComponent>())
        return;

    entity.get<PhysicsComponent, HitboxComponent, TransformComponent>([&](auto& p, auto& h, auto& t) {
        GeometryHelper::transformHitbox(h, t);

        entities.each<HitboxComponent, TransformComponent>([&](auto const& e2, auto& h2, auto& t2) {
            if (e2.getId() == entity.getId())
                return;

            GeometryHelper::transformHitbox(h2, t2);

            Manifold mf = GeometryHelper::polygonCollide(entity, h, h2);
            if (mf.isCollide) {
                if (mf.hasError)
                    return;
                p.velocity -= 2 * (p.velocity.dotProduct(mf.normal)) * mf.normal;
                p.velocity *= h.rebound * h2.rebound; // TODO: rebound velocity
                PhysicsSystem::patchCollision(entity, h2);
            }
        });
    });
}

void
engine::PhysicsSystem::patchCollision(Entity const& entity, HitboxComponent const& collideWith)
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
        if (GeometryHelper::simplePolygonCollide(h, collideWith)) {
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
engine::PhysicsSystem::applyDeplacement(Entities const& entities, Entity const& entity, bool isCorrection)
{
    entity.get<PhysicsComponent, HitboxComponent, TransformComponent>([&](auto& p, auto& h, auto& t) {
        if (p.move.X == 0.f && p.move.Y == 0.f)
            return;

        Manifold gmf;
        auto origin = t.position;
        t.prevPosition = t.position;
        t.position.X += p.move.X;
        t.position.Y += p.move.Y;
        GeometryHelper::transformHitbox(h, t);

        entities.each<HitboxComponent, TransformComponent>([&](auto const& e2, auto& h2, auto& t2) {
            if (e2.getId() == entity.getId())
                return;

            Manifold mf = GeometryHelper::polygonCollide(entity, h, h2);
            if (mf.isCollide) {
                if (mf.hasError)
                    return;
                gmf.isCollide = true;
                gmf.normal += mf.normal;
            }
        });

        if (gmf.isCollide) {
            auto dist = p.move.getLength();
            auto moveVec = p.move;
            moveVec -= 2 * (moveVec.dotProduct(gmf.normal)) * gmf.normal;
            moveVec.normalize();
            t.position = t.prevPosition;
            t.position.X += moveVec.X * std::fabs(dist);
            t.position.Y += moveVec.Y * std::fabs(dist);
            if (moveVec.dotProduct(p.move) < 0 || PhysicsSystem::simpleCollideEntities(entities, entity)) {
                t.position = t.prevPosition;
                if (!isCorrection) {
                    p.move.Y += 0.1;
                    PhysicsSystem::applyDeplacement(entities, entity, true);
                }
            }
        }
        p.move.X = 0.f;
        p.move.Y = 0.f;
        if (!isCorrection) {
            PhysicsSystem::patchDeplacement(entities, entity, origin);
        }
    });
}

void
engine::PhysicsSystem::patchDeplacement(Entities const& entities, Entity const& entity, irr::core::vector3df const& origin)
{
    bool unique = true;

    entities.withTag("map", [&](Entity const& entMap) {
        if (!unique)
            return;
        unique = false;

        auto& t = entity.get<TransformComponent>();
        auto& h = entity.get<HitboxComponent>();
        auto& hMap = entMap.get<HitboxComponent>();

        t.prevPosition = t.position;
        t.position = origin;
        t.position.Y -= 0.01;
        GeometryHelper::transformHitbox(h, t);
        t.position = t.prevPosition;
        if (!GeometryHelper::simplePolygonCollide(h, hMap))
            return;

        auto prevPos = t.position;
        bool isOk = false;
        for (auto it = 0; it < 50; it += 1) {
            t.prevPosition = t.position;
            t.position.Y -= 0.02;
            GeometryHelper::transformHitbox(h, t);
            if (GeometryHelper::simplePolygonCollide(h, hMap)) {
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
engine::PhysicsSystem::simpleCollideEntities(Entities const& entities, Entity const& entity)
{
    if (!entity.has<HitboxComponent>())
        return false;
    bool isCollide = false;

    entity.get<PhysicsComponent, HitboxComponent, TransformComponent>([&](auto& p, auto& h, auto& t) {
        GeometryHelper::transformHitbox(h, t);

        entities.each<HitboxComponent, TransformComponent>([&](auto const& e2, auto& h2, auto& t2) {
            if (e2.getId() == entity.getId())
                return;

            if (GeometryHelper::simplePolygonCollide(h, h2))
                isCollide = true;
        });
    });

    return isCollide;
}

bool
engine::PhysicsSystem::isGrounded(Entities const& entities, Entity const& entity)
{
    bool unique = true;
    bool isGrounded = false;

    entities.withTag("map", [&](Entity const& entMap) {
        if (!unique)
            return;
        unique = false;

        auto& t = entity.get<TransformComponent>();
        auto& h = entity.get<HitboxComponent>();
        auto& hMap = entMap.get<HitboxComponent>();

        t.prevPosition = t.position;
        t.position.Y -= 0.01;
        GeometryHelper::transformHitbox(h, t);
        t.position = t.prevPosition;
        std::cout << "ok" << std::endl;
        isGrounded = GeometryHelper::simplePolygonCollide(h, hMap);
    });

    return isGrounded;
}
