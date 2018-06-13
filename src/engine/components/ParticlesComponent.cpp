/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include <irrlicht/ISceneManager.h>
#include <engine/resource/ResourceManager.hpp>
#include "ParticlesComponent.hpp"

engine::ParticlesComponent::ParticlesComponent()
{}

engine::ParticlesComponent::ParticlesComponent(irr::IrrlichtDevice* device, float duration, float speed)
	: node(device->getSceneManager()->addParticleSystemSceneNode(false))
{
	irr::scene::IParticleEmitter* em = node->createBoxEmitter(
		irr::core::aabbox3d<irr::f32>(-.5f,.5f,-.5f,.5f,-.5f,.5f), // emitter size
		irr::core::vector3df(0.0f,0.01f * speed,0.f),              // initial direction
		300,500,                                                   // emit rate
		irr::video::SColor(0,255,255,255),                         // darkest color
		irr::video::SColor(0,255,255,255),                         // brightest color
		300 * duration, 500 * duration, 360,                       // min and max age, angle
		irr::core::dimension2df(.5f,.5f),                          // min size
		irr::core::dimension2df(1.f,1.f));                         // max size

	node->setEmitter(em);
	em->drop();

	irr::scene::IParticleAffector* paf = node->createFadeOutParticleAffector();

	node->addAffector(paf);
	paf->drop();

	node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	node->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	node->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}
