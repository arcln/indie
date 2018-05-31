/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Simple Parser Hpp
*/

#pragma once

#include <iostream>
#include <fstream>
#include <vector>

namespace engine { namespace Menu {

	class SimpleParser {
		public:
			SimpleParser(std::string path);
			~SimpleParser() = default;

			std::vector<std::string> getFile(std::string path);
			std::vector<std::string> getStorage() const;

		private:
			std::vector<std::string> _storage;
	};
}}
