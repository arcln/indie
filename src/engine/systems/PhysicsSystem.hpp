/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/
#pragma once

#include <vector>
#include <irrlicht/irrlicht.h>
#include "engine/core/System.hpp"
#include "engine/components/HitboxComponent.hpp"
#include "engine/components/PhysicsComponent.hpp"
#include "engine/components/TransformComponent.hpp"

namespace engine {


	class PhysicsSystem : public System {
	public:
		PhysicsSystem() = default;
		~PhysicsSystem() = default;

		void update(Scene& scene, float tick) override;

		void applyCollision(Entities& entities, Entity const& entity);
        void applyCollisionFrac(Entities& entities, Entity const& entity, float dist);
        void applyDeplacement(Entities& entities, Entity const& e);
        static void patchCollision(Entities& entities, Entity const& entity);
		static void patchCollisionFrac(Entity const& entity, Entity const& entity2);
        static void patchDeplacement(Entities& entities, Entity const& entity, irr::core::vector3df const& origin);
        static bool simpleCollideEntities(Entities& entities, Entity const& entity);
        static bool isGrounded(Entities& entities, Entity const& entity);
        static bool isImmobile(PhysicsComponent const& p);

	private:
		float _tick;
		static const Vec2D gravity;
	};
}
