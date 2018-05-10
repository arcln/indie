/*
** EPITECH PROJECT, 2017
** worms
** File description:
** A file for worms - Paul Laffitte
*/

#include <engine/core/EntityId.hpp>
#include <iostream>
#include "engine/components/ComponentPool.hpp"

void engine::ComponentPool::copyComponents(EntityId dest, EntityId src)
{
	for (auto& componentTypeIt : _components) {
		Components<AnyComponent>& entityComponents = componentTypeIt.second;
		for (auto componentIt = entityComponents.find(src); componentIt->first == src ; componentIt++) {
			if (componentIt != std::end(componentTypeIt.second)) {
				componentTypeIt.second.emplace(dest, componentIt->second);
			}
		}
	}
}
