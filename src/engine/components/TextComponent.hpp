/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Text Component Hpp
*/

#pragma once

#include <iostream>
#include <irrlicht/IGUIStaticText.h>
#include <irrlicht/IrrlichtDevice.h>
#include "engine/components/ComponentConstraint.hpp"

namespace engine {

	struct TextComponent {

		using Coords = irr::core::position2di;

		TextComponent();
		explicit TextComponent(irr::IrrlichtDevice* device, const wchar_t *text, const irr::core::rect<irr::s32> &rectangle, bool border, bool wordWrap, irr::gui::IGUIElement *parent, irr::s32 id, bool fillBackground);

		using Constraint = ComponentConstraint<TextComponent, false>;

		irr::gui::IGUIStaticText *node = nullptr;

		void move(const irr::core::position2di &pos);
	};
}