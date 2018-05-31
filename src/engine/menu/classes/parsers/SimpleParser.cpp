/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Simple Parser Cpp
*/

#include "SimpleParser.hpp"

engine::Menu::SimpleParser::SimpleParser(std::string path)
{
	getFile(path);
}

std::vector<std::string> engine::Menu::SimpleParser::getFile(std::string path)
{
	std::ifstream file(path.c_str(), std::ios::in);
	std::vector<std::string> storage;
	std::vector<std::string> tmp;
	std::string buffer;

	if (!file.is_open())
		std::cerr << "Can't open " << path << std::endl;
	while (std::getline(file, buffer))
		tmp.push_back(buffer);
	for (; tmp.empty() == false;) {
		storage.push_back(tmp.back());
		tmp.pop_back();
	}
	_storage = storage;
	return (storage);
}

std::vector<std::string> engine::Menu::SimpleParser::getStorage() const
{
	return (_storage);
}