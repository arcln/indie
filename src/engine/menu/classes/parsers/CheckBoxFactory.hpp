/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** CheckBox Factory Hpp
*/

#pragma once

#include "engine/components/CheckBoxComponent.hpp"
#include "engine/core/Game.hpp"

#include <irrlicht/SColor.h>

namespace engine { namespace Menu {

	class CheckBoxFactory {
		public:
			CheckBoxFactory(irr::gui::IGUICheckBox *node, engine::Game *game);
			~CheckBoxFactory() = default;

			std::map<std::string, std::function<void(std::string)>>	_handledFunc;

			irr::core::position2di findPos(std::string param);
			irr::video::SColor getColor(std::string param);

			int posCommand(std::string param);
			int sizeCommand(std::string param);
			int overrideFontCommand(std::string param);
			int setTextCommand(std::string param);
			int colorCommand(std::string param);
		private:
			irr::gui::IGUICheckBox *_node;
			engine::Game *_game;
			irr::IrrlichtDevice *_device;
	};
}}