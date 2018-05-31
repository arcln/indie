/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Menu Cpp
*/

#include "Menu.hpp"

engine::Menu::Menu::Menu(std::string path, std::string name, bool isFirst)
{
	std::cout << "Creation of " << name << ". Config file path is : " << path << ". Will he be displayed first ? " << isFirst << std::endl;
	_scriptFile = path;
	_menuName = name;
	_isFirst = isFirst;
	parseFile();
}

void engine::Menu::Menu::parseFile()
{
}