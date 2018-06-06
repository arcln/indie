/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Button Factory Hpp
*/

#pragma once

#include "engine/components/ButtonComponent.hpp"
#include "engine/core/Game.hpp"

namespace engine { namespace Menu {

	class ButtonFactory {
		public:
			ButtonFactory(irr::gui::IGUIButton *node, engine::Game *game);
			~ButtonFactory() = default;

			std::map<std::string, std::function<void(std::string)>>	_handledFunc;

			irr::core::rect<irr::s32> getRectPos(std::string param);

			int rectCommand(std::string param);
			int imageCommand(std::string param);
			int imagePressedCommand(std::string param);
			int borderCommand(std::string param);
			int eventCommand(std::string param);
			int setTextCommand(std::string param);
		private:
			irr::gui::IGUIButton *_node;
			engine::Game *_game;
	};
}}

