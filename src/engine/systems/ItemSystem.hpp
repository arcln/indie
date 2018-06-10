/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/
#pragma once

#include <irrlicht/irrlicht.h>
#include "engine/core/Game.hpp"
#include "engine/core/System.hpp"

namespace engine {

	class ItemSystem : public System {
	public:
		ItemSystem() = default;
		~ItemSystem() = default;

		void update(Scene& scene) override;
	};
}
