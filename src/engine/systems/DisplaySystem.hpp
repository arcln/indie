/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "System.hpp"
#include "engine/resource/ResourceManager.hpp"
#include "engine/core/Game.hpp"

namespace engine {

	class DisplaySystem : public System {
	public:
		DisplaySystem(Game& game);
		~DisplaySystem();

		void update(Components& components);

	private:
		Game& _game;
		ResourceManager<irr::scene::IAnimatedMeshSceneNode*> _nodesManager;

		irr::video::IVideoDriver* _driver = nullptr;
		irr::scene::ISceneManager* _smgr = nullptr;
		irr::gui::IGUIEnvironment* _guienv = nullptr;
	};
}
