/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Button Component Hpp
*/

#pragma once

#include <iostream>
#include <irrlicht/IGUIButton.h>
#include <irrlicht/IrrlichtDevice.h>
#include "engine/components/ComponentConstraint.hpp"

namespace engine {

	struct ButtonComponent {

		using Coords = irr::core::rect<irr::s32>;

		ButtonComponent();
		explicit ButtonComponent(irr::IrrlichtDevice* device, const irr::core::rect<irr::s32> &rectangle, irr::gui::IGUIElement *parent, irr::s32 id, const wchar_t *text, const wchar_t *tooltiptext);

		using Constraint = ComponentConstraint<ButtonComponent, false>;

		irr::gui::IGUIButton *node = nullptr;

		void move(const irr::core::rect<irr::s32> &rectangle);
	};
}