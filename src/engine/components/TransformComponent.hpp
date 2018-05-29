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

		irr::core::vector3df position;
		irr::core::vector3df rotation;
		irr::core::vector3df scale;
	};

}
