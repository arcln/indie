/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/
#include "../core/Entity.hpp"
#include "HoldSystem.hpp"
#include "../components/TransformComponent.hpp"

void
engine::HoldSystem::update(Scene& scene)
{
    Entities& entities = scene.getEntities();

    std::cout << "boucle sur les parentId des entity:" << std::endl;
    entities.each<TransformComponent>([&](Entity const& e, auto& t) {
        std::cout << e.getParentId() << std::endl;
        auto parentID = e.getParentId();

        if (parentID == Entity::nullId)
            return;

        Entity const& parent = entities.getParentEntity(e);
        std::cout << "cc3" << std::endl;

        if (parent.has<TransformComponent>()) {
            std::cout << "cc4" << std::endl;
            auto& t2 = parent.get<TransformComponent>();
            t.position.X = t2.position.X;
            t.position.Y = t2.position.Y;
        }
    });
    std::cout << std::endl;
}
