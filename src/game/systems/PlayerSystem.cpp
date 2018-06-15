/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include <engine/components/HoldComponent.hpp>
#include <engine/components/ItemComponent.hpp>
#include <engine/components/CameraComponent.hpp>
#include "engine/systems/PhysicsSystem.hpp"
#include "engine/components/PhysicsComponent.hpp"
#include "engine/components/AnimationComponent.hpp"
#include "game/components/PlayerComponent.hpp"
#include "PlayerSystem.hpp"

float const worms::PlayerSystem::_CameraSpeed = 5;
irr::core::vector3df const worms::PlayerSystem::_CameraOffset = engine::CameraComponent::Coords(0.f, 5.f, -15.f);

void
worms::PlayerSystem::update(engine::Scene& scene, float tick)
{
	engine::Entities& entities = scene.getEntities();

	entities.each<PlayerComponent, engine::PhysicsComponent, engine::AnimationComponent, engine::HoldComponent>([&entities, tick](engine::Entity const& e, auto& pl, auto& ph, auto& a, auto& hc) {
		if (engine::PhysicsSystem::isGrounded(entities, e)) {
			if (!a.playOnce)
				a.currentState = (ph.move.X == 0 ? getState("idle", hc) : getState("run", hc));
			a.playOnce = false;
		}

		entities.each<engine::CameraComponent>([e, tick](engine::Entity const& eCamera, auto& tCamera) {
			irr::core::vector3df const& oldPosition = tCamera.node->getPosition();
			irr::core::vector3df const& newPosition = e.get<engine::TransformComponent>().position + _CameraOffset;
			float ratio = tick * _CameraSpeed;

			tCamera.node->setPosition((oldPosition * (1 - ratio) + newPosition * ratio));
			tCamera.node->setTarget(e.get<engine::TransformComponent>().position);
		});
	});
}

std::string
worms::PlayerSystem::getState(std::string const& state, engine::HoldComponent const& hc)
{
	if (hc.current == -1) {
		return state;
	} else if (hc.items[hc.current].get<engine::ItemComponent>().heavy) {
		return state + "HoldHeavy";
	}

	return state;
}
