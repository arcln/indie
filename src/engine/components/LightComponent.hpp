/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <irrlicht/IrrlichtDevice.h>
#include <irrlicht/ILightSceneNode.h>

namespace engine {

	struct LightComponent {
		LightComponent();
		explicit LightComponent(irr::IrrlichtDevice* device,
					irr::core::vector3df const& position = irr::core::vector3df(0,0,0),
					irr::video::SColorf const& color = irr::video::SColorf(1.0f, 1.0f, 1.0f),
					float radius = 100.0f);

		irr::scene::ILightSceneNode* node;
	};
}
