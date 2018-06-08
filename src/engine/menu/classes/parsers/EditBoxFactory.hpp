/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** EditBox Factory Hpp
*/

#pragma once

#include "engine/components/EditBoxComponent.hpp"
#include "engine/core/Game.hpp"

#include <irrlicht/SColor.h>

namespace engine { namespace Menu {

	class EditBoxFactory {
		public:
			EditBoxFactory(irr::gui::IGUIEditBox *node, engine::Game *game);
			~EditBoxFactory() = default;

			std::map<std::string, std::function<void(std::string)>>	_handledFunc;

			irr::core::position2di findPos(std::string param);
			irr::video::SColor getColor(std::string param);

			int posCommand(std::string param);
			int sizeCommand(std::string param);
			int overrideFontCommand(std::string param);
			int setTextCommand(std::string param);
			int colorCommand(std::string param);
			int setMaxCommand(std::string param);
		private:
			irr::gui::IGUIEditBox *_node;
			engine::Game *_game;
			irr::IrrlichtDevice *_device;
	};
}}