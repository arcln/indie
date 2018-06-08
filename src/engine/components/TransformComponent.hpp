//
//  DisplayComponent.hpp
//  engine
//
//  Created by Arthur Chaloin on 09/05/2018.
//

#pragma once

#include <string>
#include <irrlicht/irrlicht.h>
#include "engine/components/ComponentConstraint.hpp"

namespace engine {

	struct TransformComponent {
		using Constraint = ComponentConstraint<TransformComponent, false>;

        irr::core::vector3df prevPosition;
        irr::core::vector3df position;
		irr::core::vector3df rotation;
        irr::core::vector3df magicPosition{0.f, 0.f, 0.f};
        irr::core::vector3df scale{1.f, 1.f, 1.f};
	};

}
