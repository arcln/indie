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
#include "engine/core/System.hpp"
#include "engine/components/HitboxComponent.hpp"
#include "engine/components/PhysicsComponent.hpp"
#include "engine/components/TransformComponent.hpp"

namespace engine {


	class PhysicsSystem : public System {
	public:
		using Clock = std::chrono::time_point<std::chrono::system_clock>;

		PhysicsSystem() = default;
		~PhysicsSystem() = default;

		void update(Scene& scene) override;

		void applyCollision(Entities& entities, Entity const& entity);
        void applyDeplacement(Entities& entities, Entity const& e, bool isCorrection = false);
		static void patchCollision(Entity const& entity, HitboxComponent const& collideWith);
        static void patchDeplacement(Entities& entities, Entity const& entity, irr::core::vector3df const& origin);
        static bool simpleCollideEntities(Entities& entities, Entity const& entity);
        static bool isGrounded(Entities& entities, Entity const& entity);

	private:
		Clock _prevUpdate = std::chrono::system_clock::now();
		float _tick;
		static const Vec2D gravity;
	};
}
