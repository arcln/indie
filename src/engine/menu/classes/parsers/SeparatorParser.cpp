/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Separator Parser Cpp
*/

#include "SeparatorParser.hpp"

engine::Menu::SeparatorParser::SeparatorParser(std::vector<std::string> storage, std::string separator)
{
	_storage = storage;
	_separator = separator;
	_rawLine = "";
	_isFinish = true;
	if (_storage.empty() == false)
		_isFinish = false;
}

std::vector<std::string> engine::Menu::SeparatorParser::reverseVector(std::vector<std::string> toReverse)
{
	std::vector<std::string> tmp;

	for (; toReverse.empty() == false;) {
		tmp.push_back(toReverse.back());
		toReverse.pop_back();
	}
	return (tmp);
}

std::vector<std::string> engine::Menu::SeparatorParser::getNextLine()
{
	std::vector<std::string> parsedLine;
	std::string tmp;
	int check = 0;
	char toAdd = 0;

	if (_storage.empty() == true)
		return parsedLine;
	_rawLine = _storage.back();
	_storage.pop_back();
	tmp = "";
	for (std::size_t i = 0; i < _rawLine.size(); i = i + 1) {
		check = 0;
		for (std::size_t j = 0; j < _separator.size(); j = j + 1) {
			if (_rawLine[i] == _separator[j])
				check = 1;
		}
		if (check == 1) {
			parsedLine.push_back(tmp);
			tmp = "";
		} else {
			toAdd = _rawLine[i];
			tmp.append(&toAdd);
		}
	}
	if (tmp != "")
		parsedLine.push_back(tmp);
	if (_storage.empty() == true)
		_isFinish = true;
	_parsedLine = reverseVector(parsedLine);
	parsedLine.clear();
	return (_parsedLine);
}

bool engine::Menu::SeparatorParser::isFinish() const
{
	return (_isFinish);
}