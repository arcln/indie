/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Button Factory Hpp
*/

#pragma once

#include "engine/components/ButtonComponent.hpp"

namespace engine { namespace Menu {

	class ButtonFactory {
		public:
			ButtonFactory(irr::gui::IGUIButton *node);
			~ButtonFactory() = default;

			std::map<std::string, std::function<void(std::string)>>	_handledFunc;

			irr::core::rect<irr::s32> getRectPos(std::string param);

			int rectCommand(std::string param);
		private:
			irr::gui::IGUIButton *_node;
	};
}}

