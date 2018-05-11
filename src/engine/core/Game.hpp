/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include <unordered_map>
#include <irrlicht/irrlicht.h>
#include "engine/core/Scene.hpp"
#include "engine/resource/ResourceManager.hpp"
#include "EventsHandler.hpp"

namespace engine {

	class System;
	using MeshNode = irr::scene::IAnimatedMesh;

	class Game {
	public:
		Game();
		virtual ~Game();

		void play(Scene& scene);
		void registerSystem(std::string const& name, System* system);

		irr::IrrlichtDevice& device();
		irr::IrrlichtDevice const& device() const;

		ResourceManager<MeshNode*> meshManager;

	private:
		irr::IrrlichtDevice* _device = nullptr;
		Event<KeyState> _keyEvents;
		EventsReceiver _eventReceiver;
		EventsHandler _eventHandler;
		std::unordered_map<std::string, System*> _systems;
	};
}
