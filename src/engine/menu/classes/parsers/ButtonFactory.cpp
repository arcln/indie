/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Button Factory Cpp
*/

#include "ButtonFactory.hpp"

engine::Menu::ButtonFactory::ButtonFactory(irr::gui::IGUIButton *node)
{
	_node = node;
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("rect", [this](std::string param) {rectCommand(param);}));
}

irr::core::rect<irr::s32> engine::Menu::ButtonFactory::getRectPos(std::string param)
{
	std::string textArg;
	int nb1 = 0;
	int nb2 = 0;
	int nb3 = 0;
	int nb4 = 0;

	for (int i = 0; i < 4; i = i + 1) {
		if (i != 3) {
			textArg = param.substr(0, param.find(',', 0));
			param = param.substr(param.find(',', 0) + 2, param.size() - param.find(',', 0) + 2);
			if (i == 1)
				nb1 = std::atoi(textArg.c_str());
			else if (i == 2)
				nb2 = std::atoi(textArg.c_str());
			else
				nb3 = std::atoi(textArg.c_str());
		} else {
			textArg = param;
			param.clear();
			nb4 = std::atoi(textArg.c_str());
		}
	}
	return irr::core::rect<irr::s32>(nb1, nb2, nb3, nb4);
}

int engine::Menu::ButtonFactory::rectCommand(std::string param)
{
	irr::core::rect<irr::s32> newPos = getRectPos(param);
	
	return 0;
}