/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Image Factory Cpp
*/

#include "ImageFactory.hpp"

engine::Menu::ImageFactory::ImageFactory(irr::gui::IGUIImage *node, engine::Game *game)
{
	_node = node;
	_game = game;
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("image", [this](std::string param) {imageCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("pos", [this](std::string param) {posCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("name", [this](std::string param) {nameCommand(param);}));
	_handledFunc.insert(std::pair<std::string, std::function<void(std::string)>>("setVisible", [this](std::string param) {setVisibleCommand(param);}));
}

int engine::Menu::ImageFactory::imageCommand(std::string param)
{
	irr::video::ITexture *image = _game->textureManager.get(param);
	_node->setImage(image);
	return 0;
}

irr::core::position2di engine::Menu::ImageFactory::findPos(std::string param)
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

int engine::Menu::ImageFactory::posCommand(std::string param)
{
	irr::core::position2di pos = findPos(param);
	_node->setRelativePosition(pos);
	return 0;
}

int engine::Menu::ImageFactory::nameCommand(std::string param)
{
	std::wstring widestr = std::wstring(param.begin(), param.end());
	const wchar_t *tmp = widestr.c_str();

	_node->setName(tmp);
	return 0;
}

int engine::Menu::ImageFactory::setVisibleCommand(std::string param)
{
	bool _bool = false;

	if (param == "true")
		_bool = true;
	else if (param == "false")
		_bool = false;
	else
		return 1;
	_node->setVisible(_bool);
	return 0;
}