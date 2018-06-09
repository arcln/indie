/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** EditBox Factory Cpp
*/

#include "EditBoxFactory.hpp"
#include <irrlicht/IGUIFont.h>

engine::Menu::EditBoxFactory::EditBoxFactory(irr::gui::IGUIEditBox *node, engine::Game *game)
{
	_node = node;
	_game = game;
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("pos", [this](std::string param) {posCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("overrideFont", [this](std::string param) {overrideFontCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("setText", [this](std::string param) {setTextCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("color", [this](std::string param) {colorCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("size", [this](std::string param) {sizeCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("setMax", [this](std::string param) {setMaxCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("setAutoScroll", [this](std::string param) {setAutoScrollCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("setDrawBackground", [this](std::string param) {setDrawBackgroundCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("setDrawBorder", [this](std::string param) {setDrawBorderCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("setMultiLine", [this](std::string param) {setMultiLineCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("setWordWrap", [this](std::string param) {setWordWrapCommand(param);}));
	_device = game->device();
}

irr::core::position2di engine::Menu::EditBoxFactory::findPos(std::string param)
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

irr::video::SColor engine::Menu::EditBoxFactory::getColor(std::string param)
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

int engine::Menu::EditBoxFactory::posCommand(std::string param)
{
	irr::core::position2di pos = findPos(param);
	_node->setRelativePosition(pos);
	return 0;
}

int engine::Menu::EditBoxFactory::overrideFontCommand(std::string param)
{
	irr::gui::IGUIFont *font = _device->getGUIEnvironment()->getFont(param.c_str());
	_node->setOverrideFont(font);
	return 0;
}

int engine::Menu::EditBoxFactory::setTextCommand(std::string param)
{
	std::wstring widestr = std::wstring(param.begin(), param.end());
	const wchar_t *tmp = widestr.c_str();

	_node->setText(tmp);
	return 0;
}

int engine::Menu::EditBoxFactory::colorCommand(std::string param)
{
	_node->setOverrideColor(getColor(param));
	return 0;
}

int engine::Menu::EditBoxFactory::sizeCommand(std::string param)
{
	irr::core::position2di size = findPos(param);
	irr::core::rect<irr::s32> currentPos = _node->getAbsolutePosition();
	irr::core::position2di pos = currentPos.UpperLeftCorner;
	irr::core::rect<irr::s32> newPos(pos.X, pos.Y, pos.X + size.X, pos.Y + size.Y);

	_node->setRelativePosition(newPos);
	return 0;
}

int engine::Menu::EditBoxFactory::setMaxCommand(std::string param)
{
	irr::s32 size = atoi(param.c_str());

	_node->setMax(size);
	return 0;
}

int engine::Menu::EditBoxFactory::setAutoScrollCommand(std::string param)
{
	bool _bool = false;

	if (param == "true")
		_bool = true;
	else if (param == "false")
		_bool = false;
	else
		return 1;
	_node->setAutoScroll(_bool);
	return 0;
}

int engine::Menu::EditBoxFactory::setDrawBackgroundCommand(std::string param)
{
	bool _bool = false;

	if (param == "true")
		_bool= true;
	else if (param == "false")
		_bool= false;
	else
		return 1;
	_node->setDrawBackground(_bool);
	return 0;
}

int engine::Menu::EditBoxFactory::setDrawBorderCommand(std::string param)
{
	bool _bool= false;

	if (param == "true")
		_bool= true;
	else if (param == "false")
		_bool= false;
	else
		return 1;
	_node->setDrawBorder(_bool);
	return 0;
}

int engine::Menu::EditBoxFactory::setMultiLineCommand(std::string param)
{
	bool _bool= false;

	if (param == "true")
		_bool= true;
	else if (param == "false")
		_bool= false;
	else
		return 1;
	_node->setMultiLine(_bool);
	return 0;
}

int engine::Menu::EditBoxFactory::setWordWrapCommand(std::string param)
{
	bool _bool= false;

	if (param == "true")
		_bool= true;
	else if (param == "false")
		_bool= false;
	else
		return 1;
	_node->setWordWrap(_bool);
	return 0;
}
