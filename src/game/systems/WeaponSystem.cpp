/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/
#include "engine/core/Entity.hpp"
#include "engine/components/TransformComponent.hpp"
#include "engine/components/PhysicsComponent.hpp"
#include "game/systems/WeaponSystem.hpp"

void
worms::WeaponSystem::update(engine::Scene& scene)
{
	engine::Entities& entities = scene.getEntities();

	entities.each<WeaponComponent>([&](engine::Entity const& e, auto& w) {
        if (e.getParentId() == engine::Entity::nullId)
            return;

        auto player = entities.getParentEntity(e);
        auto& tp = player.get<engine::TransformComponent>();
        auto& pp = player.get<engine::PhysicsComponent>();
        engine::Vec2D pos;

        if (pp.move.X == 0.f) {
            if (w.aimPosition.X < 0)
                tp.direction = false;
            else if (w.aimPosition.X > 0)
                tp.direction = true;
        }

        pos.X = w.aimPosition.X + tp.position.X;
        pos.Y = w.aimPosition.Y + tp.position.Y;
        _videoDriver->draw3DLine({pos.X - 1.f, pos.Y, 0}, {pos.X + 1.f, pos.Y, 0}, irr::video::SColor(255, 255, 0, 0));
        _videoDriver->draw3DLine({pos.X, pos.Y - 1.f, 0}, {pos.X, pos.Y + 1.f, 0}, irr::video::SColor(255, 255, 0, 0));
	});
}
