/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include "engine/core/System.hpp"
#include "engine/components/HoldComponent.hpp"

namespace worms {

	class PlayerSystem : public engine::System {
	public:
		void update(engine::Scene& scene, float tick) override;

		static std::string getState(std::string const& state, engine::HoldComponent const& hc);

	private:
		static float const _CameraSpeed;
		static irr::core::vector3df const _CameraOffset;
	};
}


