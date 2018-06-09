/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Button Factory Cpp
*/

#include "ButtonFactory.hpp"

engine::Menu::ButtonFactory::ButtonFactory(irr::gui::IGUIButton *node, engine::Game *game)
{
	_node = node;
	_game = game;
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("rect", [this](std::string param) {rectCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("image", [this](std::string param) {imageCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("imagePressed", [this](std::string param) {imagePressedCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("border", [this](std::string param) {borderCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("event", [this](std::string param) {eventCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("setText", [this](std::string param) {setTextCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("overrideFont", [this](std::string param) {overrideFontCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("setIsPushButton", [this](std::string param) {setIsPushButtonCommand(param);}));
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
	return irr::core::rect<irr::s32>(nb1, nb2, nb3, nb4);
}

int engine::Menu::ButtonFactory::rectCommand(std::string param)
{
	irr::core::rect<irr::s32> newPos = getRectPos(param);
	_node->setRelativePosition(newPos);
	return 0;
}

int engine::Menu::ButtonFactory::imageCommand(std::string param)
{
	irr::video::ITexture *image = _game->textureManager.get(param);
	_node->setImage(image);
	return 0;
}

int engine::Menu::ButtonFactory::imagePressedCommand(std::string param)
{
	irr::video::ITexture *image = _game->textureManager.get(param);
	_node->setPressedImage(image);
	return 0;
}

int engine::Menu::ButtonFactory::borderCommand(std::string param)
{
	bool border;

	if (param == "true")
		border = true;
	else if (param == "false")
		border = false;
	else {
		std::cerr << "Wrong param for border command : [" << param << "]." << std::endl;
		return 1;
	}
	_node->setDrawBorder(border);
	return 0;
}

int engine::Menu::ButtonFactory::eventCommand(std::string param)
{
	std::wstring widestr = std::wstring(param.begin(), param.end());
	const wchar_t *tmp = widestr.c_str();

	_node->setName(tmp);
	return 0;
}

int engine::Menu::ButtonFactory::setTextCommand(std::string param)
{
	std::wstring widestr = std::wstring(param.begin(), param.end());
	const wchar_t *tmp = widestr.c_str();

	_node->setText(tmp);
	return 0;
}

int engine::Menu::ButtonFactory::overrideFontCommand(std::string param)
{
	irr::IrrlichtDevice *tmp = _game->device();
	irr::gui::IGUIFont *font = tmp->getGUIEnvironment()->getFont(param.c_str());
	_node->setOverrideFont(font);
	return 0;
}

int engine::Menu::ButtonFactory::setIsPushButtonCommand(std::string param)
{
	bool _bool;

	if (param == "true")
		_bool = true;
	else if (param == "false")
		_bool = false;
	else {
		std::cerr << "Wrong param for setIsPushButton command : [" << param << "]." << std::endl;
		return 1;
	}
	_node->setIsPushButton(_bool);
	return 0;
}