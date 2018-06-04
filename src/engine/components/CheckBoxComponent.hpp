/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** CheckBox Component Hpp
*/

#pragma once

#include <iostream>
#include <irrlicht/IGUICheckBox.h>
#include <irrlicht/IrrlichtDevice.h>
#include "engine/components/ComponentConstraint.hpp"

namespace engine {

	struct CheckBoxComponent {

		using Coords = irr::core::rect<irr::s32>;

		CheckBoxComponent();
		explicit CheckBoxComponent(irr::IrrlichtDevice* device, bool checked, const irr::core::rect<irr::s32> &rectangle, irr::gui::IGUIElement *parent, irr::s32 id, const wchar_t *text);

		using Constraint = ComponentConstraint<CheckBoxComponent, false>;

		irr::gui::IGUICheckBox *node = nullptr;

		void move(const irr::core::position2di &pos);
	};
}