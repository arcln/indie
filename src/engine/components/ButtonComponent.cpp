/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Button Component Cpp
*/

#include "ButtonComponent.hpp"
#include <irrlicht/IGUIEnvironment.h>

engine::ButtonComponent::ButtonComponent()
{}

engine::ButtonComponent::ButtonComponent(irr::IrrlichtDevice* device, const irr::core::rect<irr::s32> &rectangle, irr::gui::IGUIElement *parent, irr::s32 id, const wchar_t *text, const wchar_t *tooltiptext)
{
	this->node = device->getGUIEnvironment()->addButton(rectangle, parent, id, text, tooltiptext);
}

void engine::ButtonComponent::move(const irr::core::rect<irr::s32> &rectangle)
{
	node->setRelativePosition(rectangle);
}
