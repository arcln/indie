//
//  DisplayComponent.cpp
//  engine
//
//  Created by Arthur Chaloin on 10/05/2018.
//

#include "DisplayComponent.hpp"

engine::DisplayComponent::DisplayComponent(irr::scene::ISceneManager* smgr, MeshNode* mesh)
{
	this->node = smgr->addAnimatedMeshSceneNode(mesh);
}
