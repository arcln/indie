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
	this->node = device->getSceneManager()->addCameraSceneNode(nullptr, position, lookAt);
}

void engine::CameraComponent::move(const engine::CameraComponent::Coords& delta)
{
	node->setPosition(node->getPosition() + delta);
}
