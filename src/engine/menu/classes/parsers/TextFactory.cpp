/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Text Factory Cpp
*/

#include "TextFactory.hpp"
#include <irrlicht/IGUIFont.h>

engine::Menu::TextFactory::TextFactory(irr::gui::IGUIStaticText *node, engine::Game *game)
{
	_node = node;
	_game = game;
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("pos", [this](std::string param) {posCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("overrideFont", [this](std::string param) {overrideFontCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("fontSize", [this](std::string param) {fontSizeCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("setText", [this](std::string param) {setTextCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("color", [this](std::string param) {colorCommand(param);}));
	_device = game->device();
}

irr::core::position2di engine::Menu::TextFactory::findPos(std::string param)
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

irr::video::SColor engine::Menu::TextFactory::getColor(std::string param)
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

int engine::Menu::TextFactory::posCommand(std::string param)
{
	irr::core::position2di pos = findPos(param);
	_node->setRelativePosition(pos);
	return 0;
}

int engine::Menu::TextFactory::overrideFontCommand(std::string param)
{
	irr::gui::IGUIFont *font = _device->getGUIEnvironment()->getFont(param.c_str());
	_node->setOverrideFont(font);
	return 0;
}

int engine::Menu::TextFactory::fontSizeCommand(std::string param)
{
	int size = atoi(param.c_str());
	std::string path = "../assets/font/PTSans";

	if (size != 72 && size != 68 && size != 56 && size != 48 && size != 42 && size != 36 && size != 32) {
		std::cerr << "Invalid size, availaible size are : 32, 36, 42, 48, 56, 68, 72." << std::endl;
		size = 32;
	}
	path = path + std::to_string(size) + "/PTSans" + std::to_string(size) + ".xml";
	irr::gui::IGUIFont *font = _device->getGUIEnvironment()->getFont(path.c_str());
	_node->setOverrideFont(font);
	return 0;
}

int engine::Menu::TextFactory::setTextCommand(std::string param)
{
	std::wstring widestr = std::wstring(param.begin(), param.end());
	const wchar_t *tmp = widestr.c_str();

	_node->setText(tmp);
	return 0;
}

int engine::Menu::TextFactory::colorCommand(std::string param)
{
	_node->setOverrideColor(getColor(param));
	return 0;
}