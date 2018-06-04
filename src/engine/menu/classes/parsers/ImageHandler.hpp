/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Image Handler Hpp
*/

#pragma once

#include <iostream>
#include <map>
#include <irrlicht/IGUIImage.h>

#include "engine/core/Game.hpp"

namespace engine { namespace Menu {

	class ImageHandler {
		public:
			ImageHandler(irr::gui::IGUIImage *image, engine::Game *game);
			~ImageHandler() = default;

			void applyEffects(std::string command, std::string param);

			void setFade(std::string param);
			void setFadeUnfade(std::string param);
			void setUpDown(std::string param);

			void upDownEffect();
			void upDownEffect(bool prepare, int setSpeed, int setSize);
			void fadeEffect();
			void fadeEffect(bool prepare, int setSpeed);
			void fadeUnfadeEffect();
			void fadeUnfadeEffect(bool prepare, int setSpeed);

			void runEffects();
		private:
			engine::Game							*_game;
			irr::gui::IGUIImage						*_node;
			std::string							_name;

			std::map<std::string, std::function<void (std::string)>>	_effectFunc;
			std::map<std::string, std::function<void (void)>>		_effectCall;
			std::map<std::string, bool>					_effectList;
	};
}}

