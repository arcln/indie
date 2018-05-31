/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Image Component Cpp
*/

#include "ImageComponent.hpp"
#include <irrlicht/IGUIEnvironment.h>

engine::ImageComponent::ImageComponent()
{}

engine::ImageComponent::ImageComponent(irr::IrrlichtDevice* device, irr::video::ITexture * image, irr::core::position2d<irr::s32> pos, bool useAlphaChannel = true, irr::gui::IGUIElement *parent = 0, irr::s32 id = -1, const wchar_t *text = 0)
{
	this->node = device->getGUIEnvironment()->addImage(image, pos, useAlphaChannel, parent, id, text);
}