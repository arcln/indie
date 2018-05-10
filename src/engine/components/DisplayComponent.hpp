//
//  DisplayComponent.hpp
//  engine
//
//  Created by Arthur Chaloin on 09/05/2018.
//

#pragma once

#include <string>
#include <irrlicht/irrlicht.h>
#include "Component.hpp"

namespace engine {

	using Node = irr::scene::IAnimatedMeshSceneNode;
	using MeshNode = irr::scene::IAnimatedMesh;

	struct DisplayComponent : public Component {
		DisplayComponent(irr::scene::ISceneManager* smgr, MeshNode* mesh);
		Node* node = nullptr;
	};
}
