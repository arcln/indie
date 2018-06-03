//
//  IrrlichtComponent.cpp
//  engine
//
//  Created by Arthur Chaloin on 10/05/2018.
//

#include "engine/core/Game.hpp"
#include "IrrlichtComponent.hpp"

engine::IrrlichtComponent::IrrlichtComponent()
{}

void
engine::IrrlichtComponent::initialize(Game* game, std::string const& obj)
{
    auto mesh = game->meshManager.get(obj);

	if (mesh == nullptr) {
		throw std::runtime_error("failed to load asset: '" + obj + "'");
	}

	this->node = game->device()->getSceneManager()->addAnimatedMeshSceneNode(mesh);

	if (this->node == nullptr) {
		throw std::runtime_error("failed to create node");
	}

	this->node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	this->node->setMD2Animation(irr::scene::EMAT_STAND);
}

engine::IrrlichtComponent::IrrlichtComponent(Game* game, std::string const& obj, std::string const& text)
{
    this->initialize(game, obj);
    this->node->setMaterialTexture(0, game->textureManager.get(text));
}

engine::IrrlichtComponent::IrrlichtComponent(Game* game, std::string const& obj)
{
    this->initialize(game, obj);
}
