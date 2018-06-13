/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once


#include <irrlicht/IrrlichtDevice.h>
#include <engine/utils/ComponentConstraint.hpp>
#include <irrlicht/IParticleSystemSceneNode.h>

namespace engine {

	struct ParticlesComponent {
		ParticlesComponent();
		explicit ParticlesComponent(irr::IrrlichtDevice* device, float duration = 1, float speed = 1);

		using Constraint = ComponentConstraint<ParticlesComponent, true>;

		irr::scene::IParticleSystemSceneNode* node;
	};
}
