/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include <irrlicht/ISceneManager.h>
#include "CameraComponent.hpp"

engine::CameraComponent::CameraComponent()
{}

engine::CameraComponent::CameraComponent(irr::IrrlichtDevice *device, const Coords& position, const Coords& lookAt)
{
	device->getSceneManager()->addCameraSceneNode(nullptr, position, lookAt);
}
