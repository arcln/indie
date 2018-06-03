/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/
#pragma once

#include <vector>
#include <irrlicht/irrlicht.h>
#include "engine/systems/System.hpp"
#include "engine/components/HitboxComponent.hpp"
#include "engine/components/PhysicsComponent.hpp"
#include "engine/components/TransformComponent.hpp"

namespace engine {


	class PhysicsSystem : public System {
	public:
		PhysicsSystem() = default;
		~PhysicsSystem() = default;

		void update(Entities const& entities) override;

        static void applyCollision(Entities const& entities, Entity const& entity);
        static void patchPosition(Entity const& entity, HitboxComponent const& collideWith);

	private:

		static const Vec2D gravity;
    	static const float tick;
	};
}
