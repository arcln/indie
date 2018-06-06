/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include "engine/components/LightComponent.hpp"
#include <irrlicht/ISceneManager.h>

engine::LightComponent::LightComponent()
{}

engine::LightComponent::LightComponent(irr::IrrlichtDevice* device, irr::core::vector3df const& position, irr::video::SColorf const& color, float radius)
	: node(device->getSceneManager()->addLightSceneNode(nullptr, position, color, radius)) {}
