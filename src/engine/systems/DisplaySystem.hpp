/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "engine/core/Game.hpp"
#include "engine/resource/ResourceManager.hpp"
#include "engine/systems/System.hpp"

namespace engine {

	class DisplaySystem : public System {
	public:
		DisplaySystem(Game& game);
		~DisplaySystem();

		void update(Entities const& entities) override;

	private:
		Game& _game;
		ResourceManager<irr::scene::IAnimatedMeshSceneNode*> _nodesManager;

		irr::video::IVideoDriver* _videoDriver;
		irr::scene::ISceneManager* _sceneManager;
		irr::gui::IGUIEnvironment* _guiEnv;
	};
}
