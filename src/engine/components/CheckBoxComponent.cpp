/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** CheckBox Component Cpp
*/

#include "CheckBoxComponent.hpp"
#include <irrlicht/IGUIEnvironment.h>

engine::CheckBoxComponent::CheckBoxComponent()
{}

engine::CheckBoxComponent::CheckBoxComponent(irr::IrrlichtDevice* device, bool checked, const irr::core::rect<irr::s32> &rectangle, irr::gui::IGUIElement *parent, irr::s32 id, const wchar_t *text)
{
	this->node = device->getGUIEnvironment()->addCheckBox(checked, rectangle, parent, id, text);
}

void engine::CheckBoxComponent::move(const irr::core::position2di &pos)
{
	node->setRelativePosition(pos);
}