/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Image Factory Hpp
*/

#pragma once

#include "engine/components/ImageComponent.hpp"
#include "engine/core/Game.hpp"

namespace engine { namespace Menu {

	class ImageFactory {
		public:
			ImageFactory(irr::gui::IGUIImage *node, engine::Game *game);
			~ImageFactory() = default;

			std::map<std::string, std::function<void(std::string)>>	_handledFunc;

			irr::core::position2di findPos(std::string param);

			int imageCommand(std::string param);
			int posCommand(std::string param);
			int nameCommand(std::string param);
			int setVisibleCommand(std::string param);
		private:
			irr::gui::IGUIImage *_node;
			engine::Game *_game;
	};
}}

