/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include "engine/systems/PhysicsSystem.hpp"
#include "engine/components/PhysicsComponent.hpp"
#include "engine/components/AnimationComponent.hpp"
#include "game/components/PlayerComponent.hpp"
#include "PlayerSystem.hpp"

void
worms::PlayerSystem::update(engine::Scene& scene)
{
	engine::Entities& entities = scene.getEntities();

	entities.each<PlayerComponent, engine::PhysicsComponent, engine::AnimationComponent>([&scene](engine::Entity const& e, auto& pl, auto& ph, auto& a) {
		if (engine::PhysicsSystem::isGrounded(scene.getEntities(), e) && !a.playOnce) {
			a.currentState = (ph.move.X == 0 ? "idle" : "run");
			a.playOnce = false;
		}
	});
}
