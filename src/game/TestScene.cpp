/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include <iostream>
#include "TestScene.hpp"
#include "engine/components/TestComponent.hpp"

testGame::TestScene::TestScene()
{
	this->registerModel("test", [](engine::Entity const& entity) -> void {
		std::shared_ptr<engine::TestComponent> testComponent = entity.addTestComponent();
	});

	_entity = &this->spawnEntity("test");
}

testGame::TestScene::~TestScene()
{
}

void testGame::TestScene::update()
{
}
