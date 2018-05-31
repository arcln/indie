/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Menu Engine Cpp
*/

#include "MenuEngine.hpp"

engine::Menu::MenuEngine::MenuEngine(std::string path, engine::Game &game, engine::Scene &scene)
{
	_pathScript = path;
	engine::Menu::SimpleParser parser(path);
	std::vector<std::string> storage = parser.getStorage();
	engine::Menu::SeparatorParser secondParser(storage, std::string(":"));
	for (; secondParser.isFinish() == false;) {
		createMenu(secondParser.getNextLine());
	}
}

void engine::Menu::MenuEngine::createMenu(std::vector<std::string> informations)
{
	std::string name;
	std::string path;
	std::string strIsFirst;
	bool isFirst;

	if (informations.size() != 3) {
		std::cerr << "Error in createMenu: Need 3 informations" << std::endl;
		return;
	}
	name = informations.back();
	informations.pop_back();
	path = informations.back();
	informations.pop_back();
	strIsFirst = informations.back();
	informations.pop_back();
	isFirst = strIsFirst == "true" ? true : false;
	std::map<std::string, engine::Menu::Menu>::iterator it = _menuList.find(name);
	if (it == _menuList.end())
		_menuList.insert(std::pair<std::string, engine::Menu::Menu>(name, engine::Menu::Menu(path, name, isFirst)));
	else
		std::cerr << "Menu " << name << " already exist." << std::endl;
}