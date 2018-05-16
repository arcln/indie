/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#pragma once

#include <string>
#include <irrlicht/ICameraSceneNode.h>
#include <irrlicht/IrrlichtDevice.h>

namespace engine {

	struct CameraComponent {
		using Coords = irr::core::vector3df;

		CameraComponent();
		explicit CameraComponent(irr::IrrlichtDevice* device, Coords const& position = Coords(0, 0, 0), Coords const& lookAt = Coords(0, 0, 1));

		irr::scene::ICameraSceneNode* node = nullptr;

		void move(Coords const& delta);
	};
}
