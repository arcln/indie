/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include "engine/core/Game.hpp"
#include "engine/core/Scene.hpp"

namespace worms {

	class EntityModeller {
	public:
		EntityModeller(engine::Game& game, engine::Scene& scene);

		virtual void operator()(engine::Entity const& entity) = 0;

	protected:
		engine::Game& _game;
		engine::Scene& _scene;
	};

	class Player : public EntityModeller {
	public:
		Player(engine::Game& game, engine::Scene& scene);

		void operator()(engine::Entity const& entity) override;

	private:
	};
}
