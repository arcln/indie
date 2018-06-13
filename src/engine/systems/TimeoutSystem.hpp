/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include "engine/core/System.hpp"

namespace engine {

	class TimeoutSystem : public System {
	public:
		void update(Scene& scene, float tick) override;
	};
}
