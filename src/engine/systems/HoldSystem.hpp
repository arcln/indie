/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/
#pragma once

#include <irrlicht/irrlicht.h>
#include "engine/systems/System.hpp"

namespace engine {

	class HoldSystem : public System {
	public:
		HoldSystem() = default;
		~HoldSystem() = default;

		void update(Scene& scene) override;
	};
}
