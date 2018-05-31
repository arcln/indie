/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Image Component Hpp
*/

#pragma once

#include <iostream>
#include <irrlicht/IGUIImage.h>
#include <irrlicht/IrrlichtDevice.h>
#include "engine/components/ComponentConstraint.hpp"


namespace engine {
	
	struct ImageComponent {

		using Coords = irr::core::rect<irr::s32>;

		ImageComponent();
		explicit ImageComponent(irr::IrrlichtDevice* device, irr::video::ITexture * image, irr::core::position2d<irr::s32> pos, bool useAlphaChannel, irr::gui::IGUIElement *parent, irr::s32 id, const wchar_t *text);

		using Constraint = ComponentConstraint<ImageComponent, false>;

		irr::gui::IGUIImage *node = nullptr;

		void move(const irr::core::rect<irr::s32> &rectangle);
	};
}

