/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "Scene.hpp"
#include "engine/resource/ResourceManager.hpp"

namespace engine {

	class Mesh;

	class Game {
	public:
		Game();
		virtual ~Game();

		void play(Scene& scene);

		irr::IrrlichtDevice& device();
		irr::IrrlichtDevice const& device() const;

		ResourceManager<Mesh*> meshManager;

	private:
		irr::IrrlichtDevice* _device = nullptr;
	};
}
