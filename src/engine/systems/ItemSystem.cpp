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

void
engine::ItemSystem::update(Scene& scene)
{
    int64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() % 1000000;
    Entities& entities = scene.getEntities();

    entities.each<TransformComponent>([&](Entity const& e, auto& t) {
        auto parentID = e.getParentId();

        if (e.has<ItemComponent>() && parentID == Entity::nullId) {
            t.rotation.Y += 1.f;
            t.magicPosition.Y = (0.5f + (std::cos(now / 500.f) / 2.f)) / 2.f;
        } else {
            t.rotation.Y = 0.f;
            t.magicPosition.Y = 0.f;
        }

        if (parentID == Entity::nullId)
            return;

        Entity const& parent = entities.getParentEntity(e);

        if (parent.has<TransformComponent>()) {
            auto& t2 = parent.get<TransformComponent>();
            t.position.X = t2.position.X;
            t.position.Y = t2.position.Y;

            if (e.has<ItemComponent>()) {
                auto& i = e.get<ItemComponent>();
                t.position.X += i.offset.X;
                t.position.Y += i.offset.Y;
                t.position.Z += i.offset.Z;
            }
        }
    });
}
