//
//  ProgressBarComponent.hpp
//  bomberman
//
//  Created by Arthur Chaloin on 15/06/2018.
//

#pragma once

#include "engine/utils/ComponentConstraint.hpp"

namespace engine {

	struct ProgressBarComponent {
		using Constraint = engine::ComponentConstraint<ProgressBarComponent, false>;

		float progress;
	};
}
