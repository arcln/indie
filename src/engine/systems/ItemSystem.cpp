/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/
#include <cmath>
#include <chrono>
#include "../core/Entity.hpp"
#include "ItemSystem.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/HoldComponent.hpp"
#include "../components/ItemComponent.hpp"
#include "../components/HitboxComponent.hpp"

/*

sqrt( (A.x - C.x) ** 2 + (A.y - (C.x * 2 + 1)) ** 2 ) =  dist

*/

void
engine::ItemSystem::update(Scene& scene, float)
{
    int64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() % 1000000;
    Entities& entities = scene.getEntities();

    entities.each<TransformComponent, ItemComponent, HitboxComponent>([&](Entity const& e, auto& t, auto& i, auto& h) {
        auto parentID = e.getParentId();

        if (e.has<ItemComponent>() && parentID == Entity::nullId) {
            t.rotation.Y += 1.f;
            t.magicPosition.Y = (0.5f + (std::cos(now / 500.f) / 2.f)) / 2.f;
        }

        if (parentID == Entity::nullId)
            return;

        Entity const& parent = entities.getParentEntity(e);
        if (parent.has<TransformComponent>()) {
            auto& t2 = parent.get<TransformComponent>();
            t.position.X = t2.position.X;
            t.position.Y = t2.position.Y;

            if (e.has<ItemComponent>()) {
                t.position.X += i.offset.X;
                t.position.Y += i.offset.Y;
                t.position.Z += i.offset.Z;
            }
        }
        auto& parentH = parent.get<HitboxComponent>();
        i.direction = true;
        if (!parent.get<TransformComponent>().direction) {
            i.direction = false;
            t.position.X -= (h.WSize.X - parentH.WSize.X / 2);
            t.rotation.Y = 180.f;
        } else {
            t.rotation.Y = 0.f;
        }
        t.magicPosition.Y = 0.f;
    });
}
