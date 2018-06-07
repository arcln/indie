//
//  MasterComponent.hpp
//  worms
//
//  Created by Arthur Chaloin on 07/06/2018.
//

#pragma once

#include "engine/components/ComponentConstraint.hpp"

namespace worms {

	struct MasterComponent {
		using Constraint = engine::ComponentConstraint<MasterComponent, false>;

		int currentPlayer;
	};
}
