/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Text Factory Hpp
*/

#pragma once

#include "engine/components/TextComponent.hpp"
#include "engine/core/Game.hpp"

#include <irrlicht/SColor.h>

namespace engine { namespace Menu {

	class TextFactory {
		public:
			TextFactory(irr::gui::IGUIStaticText *node, engine::Game *game);
			~TextFactory() = default;

			std::map<std::string, std::function<void(std::string)>>	_handledFunc;

			irr::core::position2di findPos(std::string param);
			irr::video::SColor getColor(std::string param);

			int posCommand(std::string param);
			int overrideFontCommand(std::string param);
			int setTextCommand(std::string param);
			int colorCommand(std::string param);
		private:
			irr::gui::IGUIStaticText *_node;
			engine::Game *_game;
			irr::IrrlichtDevice *_device;
	};
}}