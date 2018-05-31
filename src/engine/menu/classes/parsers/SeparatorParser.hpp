/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Separator Parser Hpp
*/

#pragma once

#include <iostream>
#include <vector>

namespace engine { namespace Menu {

	class SeparatorParser {
		public:
			SeparatorParser(std::vector<std::string> storage, std::string separator);
			~SeparatorParser() = default;

			std::vector<std::string> getNextLine();
			std::vector<std::string> reverseVector(std::vector<std::string> toReverse);
			bool isFinish() const;
		private:
			std::vector<std::string>	_storage;
			std::vector<std::string>	_parsedLine;
			std::string			_rawLine;
			std::string			_separator;
			bool				_isFinish;
	};
}}

