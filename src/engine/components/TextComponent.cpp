/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Text Component Cpp
*/

#include "TextComponent.hpp"
#include <irrlicht/IGUIEnvironment.h>

engine::TextComponent::TextComponent()
{}

engine::TextComponent::TextComponent(irr::IrrlichtDevice* device, const wchar_t *text, const irr::core::rect<irr::s32> &rectangle, bool border, bool wordWrap, irr::gui::IGUIElement *parent, irr::s32 id, bool fillBackground)
{
	this->node = device->getGUIEnvironment()->addStaticText(text, rectangle, border, wordWrap, parent, id, fillBackground);
}

void engine::TextComponent::move(const irr::core::position2di &pos)
{
	node->setRelativePosition(pos);
}