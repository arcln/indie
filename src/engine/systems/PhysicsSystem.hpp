/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/
#pragma once

#include <vector>
#include <chrono>
#include <irrlicht/irrlicht.h>
#include "engine/systems/System.hpp"
#include "engine/components/HitboxComponent.hpp"
#include "engine/components/PhysicsComponent.hpp"
#include "engine/components/TransformComponent.hpp"

namespace engine {


	class PhysicsSystem : public System {
	public:
        using Clock = std::chrono::time_point<std::chrono::system_clock>;

		PhysicsSystem() = default;
		~PhysicsSystem() = default;

		void update(Entities const& entities) override;

        static void applyCollision(Entities const& entities, Entity const& entity);
        static void patchCollision(Entity const& entity, HitboxComponent const& collideWith);
        static void applyDeplacement(Entities const& entities, Entity const& e, bool isCorrection = false);
        static void patchDeplacement(Entities const& entities, Entity const& entity, irr::core::vector3df const& origin);
        static bool simpleCollideEntities(Entities const& entities, Entity const& entity);
        static bool isGrounded(Entities const& entities, Entity const& entity);

	private:
        Clock _prevUpdate = std::chrono::system_clock::now();
        float _tick;
		static const Vec2D gravity;
	};
}
