/*
 ** EPITECH PROJECT, 2018
 ** Indie
 ** File description:
 ** Text Component Hpp
 */

#pragma once

#include <irrlicht/irrlicht.h>
#include "engine/utils/ComponentConstraint.hpp"

namespace engine {

	struct RectComponent {
		using Constraint = ComponentConstraint<RectComponent, false>;

		RectComponent() = default;
		explicit RectComponent(irr::IrrlichtDevice* device);

		irr::core::rect<float>* node = nullptr;
	};
}
