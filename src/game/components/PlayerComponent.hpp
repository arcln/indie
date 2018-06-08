//
//  PlayerComponent.hpp
//  engine
//
//  Created by Arthur Chaloin on 06/06/2018.
//

#pragma once

#include "engine/utils/ComponentConstraint.hpp"

namespace worms {

	struct PlayerComponent {
		using Constraint = engine::ComponentConstraint<PlayerComponent, false>;

		explicit PlayerComponent(int id) : id(id) {}

		int id;
		int hp = 100;
	};
}
