/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include "engine/core/System.hpp"

namespace worms {

	class PlayerSystem : public engine::System {
	public:
		void update(engine::Scene& scene) override;
	};
}


