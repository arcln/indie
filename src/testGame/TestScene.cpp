/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include <iostream>
#include "TestScene.hpp"
#include "../engine/components/TestComponent.hpp"

testGame::TestScene::TestScene()
{
	this->makeModel("test", [](engine::Entity const& entity) -> void {
		engine::TestComponent component{};

		component.value = 41;
		entity.addComponent(component);
	});

	_entity = &this->spawnEntity("test");
}

testGame::TestScene::~TestScene()
{
}

void testGame::TestScene::update()
{
}
