/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** EditBox Component Hpp
*/

#pragma once

#include <iostream>
#include <irrlicht/IGUIEditBox.h>
#include <irrlicht/IrrlichtDevice.h>
#include "engine/components/ComponentConstraint.hpp"

namespace engine {

	struct EditBoxComponent {

		using Coords = irr::core::position2di;

		EditBoxComponent();
		explicit EditBoxComponent(irr::IrrlichtDevice* device, const wchar_t *text, const irr::core::rect<irr::s32> &rectangle, bool border, irr::gui::IGUIElement *parent, irr::s32 id);

		using Constraint = ComponentConstraint<EditBoxComponent, false>;

		irr::gui::IGUIEditBox *node = nullptr;

		void move(const irr::core::position2di &pos);
	};
}