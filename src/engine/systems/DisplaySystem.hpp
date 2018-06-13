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
#include "engine/core/System.hpp"

namespace engine {

	class DisplaySystem : public System {
	public:
		DisplaySystem(Game& game);
		~DisplaySystem();

		void update(Scene& scene, float tick) override;

	private:
		Game& _game;

		irr::video::IVideoDriver* _videoDriver;
		irr::scene::ISceneManager* _sceneManager;
		irr::gui::IGUIEnvironment* _guiEnv;
	};
}
