//
//  IrrlichtComponent.hpp
//  engine
//
//  Created by Arthur Chaloin on 21/05/2018.
//

#pragma once

#include <irrlicht/irrlicht.h>
#include "engine/core/Game.hpp"

namespace engine {

	struct IrrlichtComponent {
		using Constraint = ComponentConstraint<IrrlichtComponent, false>;

		IrrlichtComponent();
        IrrlichtComponent(Game* game, std::string const& obj, std::string const& text);
		IrrlichtComponent(Game* game, std::string const& obj);

		irr::scene::IAnimatedMeshSceneNode* node = nullptr;

    private:
        void initialize(Game* game, std::string const& obj);
	};
}
