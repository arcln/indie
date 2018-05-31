/*
** EPITECH PROJECT, 2018
** cpp_indie
** File description:
** Menu Engine Hpp
*/

#pragma once

#include <vector>
#include <map>
#include <iostream>
#include <irrlicht/irrlicht.h>

#include "Menu.hpp"
#include "engine/core/Game.hpp"

namespace engine { namespace Menu {

	class MenuEngine {
		public:
			MenuEngine(std::string path, engine::Game &game, engine::Scene &scene);
			~MenuEngine() = default;

			void createMenu(std::vector<std::string> informations);
		protected:
			std::string					_pathScript;
			std::map<std::string, engine::Menu::Menu>	_menuList;
	};
}}