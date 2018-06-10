/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** EditBox Component Cpp
*/

#include "EditBoxComponent.hpp"
#include <irrlicht/IGUIEnvironment.h>

engine::EditBoxComponent::EditBoxComponent()
{}

engine::EditBoxComponent::EditBoxComponent(irr::IrrlichtDevice* device, const wchar_t *text, const irr::core::rect<irr::s32> &rectangle, bool border, irr::gui::IGUIElement *parent, irr::s32 id)
{
	this->node = device->getGUIEnvironment()->addEditBox(text, rectangle, border, parent, id);
}

void engine::EditBoxComponent::move(const irr::core::position2di &pos)
{
	node->setRelativePosition(pos);
}