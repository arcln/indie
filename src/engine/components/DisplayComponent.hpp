//
//  DisplayComponent.hpp
//  engine
//
//  Created by Arthur Chaloin on 09/05/2018.
//

#pragma once

#include <string>
#include <irrlicht/irrlicht.h>

namespace engine {

	struct DisplayComponent {
		DisplayComponent();
		DisplayComponent(class Game* game, std::string const& asset);

		irr::scene::IAnimatedMeshSceneNode* node = nullptr;
	};
}
