/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Image Handler Cpp
*/

#include "ImageHandler.hpp"

engine::Menu::ImageHandler::ImageHandler(irr::gui::IGUIImage *image, engine::Game *game)
{
	_node = image;
	_game = game;
	_name = "";
	_effectList.insert(std::pair<std::string, bool>("fade", false));
	_effectList.insert(std::pair<std::string, bool>("fadeUnfade", false));
	_effectList.insert(std::pair<std::string, bool>("upDown", false));
	_effectFunc.insert(std::pair<std::string, std::function<void (std::string)>>("fade", [this](std::string param) {setFade(param);}));
	_effectFunc.insert(std::pair<std::string, std::function<void (std::string)>>("fadeUnfade", [this](std::string param) {setFadeUnfade(param);}));
	_effectFunc.insert(std::pair<std::string, std::function<void (std::string)>>("upDown", [this](std::string param) {setUpDown(param);}));
	_effectCall.insert(std::pair<std::string, std::function<void (void)>>("fade", [this](void) {fadeEffect();}));
	_effectCall.insert(std::pair<std::string, std::function<void (void)>>("fadeUnfade", [this](void) {fadeUnfadeEffect();}));
	_effectCall.insert(std::pair<std::string, std::function<void (void)>>("upDown", [this](void) {upDownEffect();}));
}

void engine::Menu::ImageHandler::applyEffects(std::string command, std::string param)
{
	if (command == "name") {
		_name = param;
		return;
	}
	std::string effectName = param.substr(0, param.find(' ', 0));
	param = param.substr(param.find(' ', 0), param.size() - param.find(' ', 0));
	std::cout << "Effect : " << effectName << std::endl;
	for (std::pair<std::string, std::function<void (std::string)>> elem : _effectFunc) {
		if (elem.first == effectName)
			elem.second(param);
	}
}

void engine::Menu::ImageHandler::setFade(std::string param)
{
	std::cout << "DEBUG : set Fade : " <<  param << std::endl;
}

void engine::Menu::ImageHandler::setFadeUnfade(std::string param)
{
	std::cout << "DEBUG : set FadeUnFade : " << param << std::endl;
}

void engine::Menu::ImageHandler::setUpDown(std::string param)
{
	std::cout << "DEBUG : set UpDown : " << param << std::endl;
}

void engine::Menu::ImageHandler::upDownEffect()
{
	upDownEffect(false, 0, 0);
}

void engine::Menu::ImageHandler::upDownEffect(bool prepare, int setSpeed, int setSize)
{
	static int speed = 0;
	static int size = 0;
	static bool isUp = false;
	static int comSize = 0;

	if (prepare == true) {
		speed = setSpeed;
		size = setSize;
		return;
	}
	irr::core::rect<irr::s32> pos = _node->getRelativePosition();
	irr::core::position2di upLeft = pos.UpperLeftCorner;
	irr::core::position2di lowRight = pos.LowerRightCorner;

	if (isUp == false) {
		comSize += 1;
		upLeft.X -= speed;
		lowRight.X -= speed;
		_node->setRelativePosition(upLeft);
	} else {
		comSize -= 1;
		upLeft.X += speed;
		_node->setRelativePosition(upLeft);
	}
	if (comSize == size)
		isUp = true;
	else if (comSize == 0)
		isUp = false;
	std::cout << "Lol ?" << std::endl;
}

void engine::Menu::ImageHandler::fadeEffect()
{
	fadeEffect(false, 0);
}

void engine::Menu::ImageHandler::fadeEffect(bool prepare, int setSpeed)
{
	static int speed = 0;

	if (prepare == true) {
		speed = setSpeed;
		return;
	}
}

void engine::Menu::ImageHandler::fadeUnfadeEffect()
{
	fadeUnfadeEffect(false, 0);
}

void engine::Menu::ImageHandler::fadeUnfadeEffect(bool prepare, int setSpeed)
{
	static int speed = 0;

	if (prepare == true) {
		speed = setSpeed;
		return;
	}
}

void engine::Menu::ImageHandler::runEffects()
{
	for (std::pair<std::string, bool> elem : _effectList) {
		if (elem.second == true) {
			for (std::pair<std::string, std::function<void (void)>> func : _effectCall) {
				if (func.first == elem.first)
					func.second();
			}
		}
	}
}