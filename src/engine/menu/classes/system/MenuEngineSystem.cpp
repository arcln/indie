/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Engine Menu System Cpp
*/

#include "MenuEngineSystem.hpp"
#include "engine/components/ButtonComponent.hpp"
#include "engine/components/IrrlichtComponent.hpp"

engine::Menu::MenuEngineSystem::MenuEngineSystem()
{
}

engine::Menu::MenuEngineSystem::~MenuEngineSystem()
{
}

void engine::Menu::MenuEngineSystem::update(Scene &scene)
{
	Entities entities = scene.getEntities();
	entities.each<ButtonComponent>([&](auto const& e, auto& button) {
		if (button.node->isPressed() == true) {
			if (button.node->getName() != "") {
				std::cout << "Event -> " << button.node->getName() << std::endl;
				scene.triggerEvent<bool>(button.node->getName(), false);
			}
		}
	});
}