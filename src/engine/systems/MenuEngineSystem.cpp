/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Engine Menu System Cpp
*/

#include "MenuEngineSystem.hpp"
#include "engine/components/ButtonComponent.hpp"
#include "engine/components/ImageComponent.hpp"
#include "engine/components/IrrlichtComponent.hpp"

engine::Menu::MenuEngineSystem::MenuEngineSystem()
{
}

engine::Menu::MenuEngineSystem::~MenuEngineSystem()
{
}

void engine::Menu::MenuEngineSystem::update(Scene &scene, float)
{
	Entities entities = scene.getEntities();
	entities.each<ButtonComponent>([&](auto const& e, auto& button) {
		if (button.node->isPressed() == true) {
			std::string name = button.node->getName();
			if (name != "")
				scene.triggerEvent<bool>(button.node->getName(), false);
		}
		(void) e;
	});
	entities.each<ImageComponent>([&](auto const& e, auto& image) {
		std::string name = image.node->getName();
		if (name == "spinner0") {
			scene.triggerEvent<bool>("spin", true);
		}
		(void) e;
	});
}