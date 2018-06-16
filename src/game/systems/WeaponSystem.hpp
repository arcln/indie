/*
** EPITECH PROJECT, 2017
** ECS Engine
** File description:
** Thomas Arbona
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "engine/core/System.hpp"
#include "engine/core/Game.hpp"
#include "game/components/WeaponComponent.hpp"

namespace worms {

	class WeaponSystem : public engine::System {
	public:
        WeaponSystem(engine::Game& game) : _game(game) {}

		void update(engine::Scene& scene, float tick) override;

    private:
        engine::Game& _game;

		static constexpr float _Pi();
		static constexpr float _RadiansDegrees();
	};
}
