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
        WeaponSystem(engine::Game& game) : _videoDriver(game.device()->getVideoDriver()) {}

		void update(engine::Scene& scene) override;

    private:
        irr::video::IVideoDriver* _videoDriver;
	};
}
