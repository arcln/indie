/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** CheckBox Factory Cpp
*/

#include "CheckBoxFactory.hpp"
#include <irrlicht/IGUIFont.h>

engine::Menu::CheckBoxFactory::CheckBoxFactory(irr::gui::IGUICheckBox *node, engine::Game *game)
{
	_node = node;
	_game = game;
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("pos", [this](std::string param) {posCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("setText", [this](std::string param) {setTextCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("size", [this](std::string param) {sizeCommand(param);}));
	_device = game->device();
}

irr::core::position2di engine::Menu::CheckBoxFactory::findPos(std::string param)
{
	std::string textArg;
	int nb1 = 0;
	int nb2 = 0;

	for (int i = 0; i < 2; i = i + 1) {
		if (i != 1) {
			textArg = param.substr(0, param.find(',', 0));
			param = param.substr(param.find(',', 0) + 2, param.size() - param.find(',', 0) + 2);
			if (i == 0)
				nb1 = std::atoi(textArg.c_str());
		} else {
			textArg = param;
			param.clear();
			nb2 = std::atoi(textArg.c_str());
		}
	}
	return irr::core::position2di(nb1, nb2);
}

irr::video::SColor engine::Menu::CheckBoxFactory::getColor(std::string param)
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
			if (i == 0)
				nb1 = std::atoi(textArg.c_str());
			else if (i == 1)
				nb2 = std::atoi(textArg.c_str());
			else
				nb3 = std::atoi(textArg.c_str());
		} else {
			textArg = param;
			param.clear();
			nb4 = std::atoi(textArg.c_str());
		}
	}
	return irr::video::SColor(nb1, nb2, nb3, nb4);
}

int engine::Menu::CheckBoxFactory::posCommand(std::string param)
{
	irr::core::position2di pos = findPos(param);
	_node->setRelativePosition(pos);
	return 0;
}

int engine::Menu::CheckBoxFactory::setTextCommand(std::string param)
{
	std::wstring widestr = std::wstring(param.begin(), param.end());
	const wchar_t *tmp = widestr.c_str();

	_node->setText(tmp);
	return 0;
}

int engine::Menu::CheckBoxFactory::sizeCommand(std::string param)
{
	irr::core::position2di size = findPos(param);
	irr::core::rect<irr::s32> currentPos = _node->getAbsolutePosition();
	irr::core::position2di pos = currentPos.UpperLeftCorner;
	irr::core::rect<irr::s32> newPos(pos.X, pos.Y, pos.X + size.X, pos.Y + size.Y);

	_node->setRelativePosition(newPos);
	return 0;
}