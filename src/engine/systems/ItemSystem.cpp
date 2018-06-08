/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/
#include "../core/Entity.hpp"
#include "ItemSystem.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/HoldComponent.hpp"
#include "../components/ItemComponent.hpp"

void
engine::ItemSystem::update(Scene& scene)
{
    Entities& entities = scene.getEntities();

    entities.each<TransformComponent>([&](Entity const& e, auto& t) {
        auto parentID = e.getParentId();

        if (e.has<ItemComponent>() && parentID == Entity::nullId) {
            t.rotation.Y += 1.f;
            t.magicPosition.Y = 1.f;
        }

        if (parentID == Entity::nullId)
            return;

        Entity const& parent = entities.getParentEntity(e);

        if (parent.has<TransformComponent>()) {
            auto& t2 = parent.get<TransformComponent>();
            t.position.X = t2.position.X;
            t.position.Y = t2.position.Y;
        }
    });
}