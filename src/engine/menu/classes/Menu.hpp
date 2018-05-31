/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Menu Hpp
*/

#pragma once

#include <iostream>
#include <map>

#include "./parsers/SimpleParser.hpp"
#include "./parsers/SeparatorParser.hpp"
#include "./parsers/MyScriptParser.hpp"

namespace engine { namespace Menu {

	class Menu {
		public:
			Menu(std::string path, std::string name, bool isFirst);
			virtual ~Menu() = default;

			void parseFile();
		private:
			std::string				_menuName;
			bool					_isFirst;
			std::string				_scriptFile;
	};
}}