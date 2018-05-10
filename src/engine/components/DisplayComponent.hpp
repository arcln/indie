//
//  DisplayComponent.hpp
//  engine
//
//  Created by Arthur Chaloin on 09/05/2018.
//

#pragma once

#include <string>
#include <irrlicht/irrlicht.h>
#include "engine/core/Game.hpp"
#include "engine/components/Component.hpp"

namespace engine {

	using Node = irr::scene::IAnimatedMeshSceneNode;

	struct DisplayComponent : public Component {
		DisplayComponent(Game& game, std::string const& asset);

		Node* node = nullptr;
	};
}
