/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/
#include "engine/core/Entity.hpp"
#include "engine/components/TransformComponent.hpp"
#include "engine/components/PhysicsComponent.hpp"
#include "engine/components/CameraComponent.hpp"
#include "game/systems/WeaponSystem.hpp"

void
worms::WeaponSystem::update(engine::Scene& scene)
{
	engine::Entities& entities = scene.getEntities();

    auto mousePos = _game.eventsHandler.getMousePosition();
    auto videoDriver = _game.device()->getVideoDriver();
    irr::core::vector3df mousePos3D(0.f, 0.f, 0.f);

    entities.each<engine::CameraComponent>([&](auto const& e, auto& c) {
        irr::core::line3df ray = _game.device()->getSceneManager()->getSceneCollisionManager()->getRayFromScreenCoordinates(mousePos, c.node);
        irr::core::plane3df plane({0.f, 0.f, 0.f}, irr::core::vector3df(0, 0, -1));

        plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePos3D);
    });

	entities.each<WeaponComponent>([&](engine::Entity const& e, auto& w) {
        if (e.getParentId() == engine::Entity::nullId)
            return;

        auto player = entities.getParentEntity(e);
        auto& tp = player.get<engine::TransformComponent>();
        auto& pp = player.get<engine::PhysicsComponent>();

        w.aimPosition.X = mousePos3D.X - tp.position.X;
        w.aimPosition.Y = mousePos3D.Y - tp.position.Y;

        if (pp.move.X == 0.f) {
            if (w.aimPosition.X < 0)
                tp.direction = false;
            else if (w.aimPosition.X > 0)
                tp.direction = true;
        }

        videoDriver->draw3DLine({mousePos3D.X - 1.f, mousePos3D.Y, 0}, {mousePos3D.X + 1.f, mousePos3D.Y, 0}, irr::video::SColor(255, 255, 0, 0));
        videoDriver->draw3DLine({mousePos3D.X, mousePos3D.Y - 1.f, 0}, {mousePos3D.X, mousePos3D.Y + 1.f, 0}, irr::video::SColor(255, 255, 0, 0));
	});
}
