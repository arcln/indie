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
	this->registerModel("test", [](engine::Entity const& entity) -> engine::Entity const& {
		engine::TestComponent& testComponent = entity.addComponent<engine::TestComponent>();
		testComponent.value = 42;
		return entity;
	});

	_entity = &this->spawnEntity("test");
	_entity2 = &this->spawnEntity("test");
}

testGame::TestScene::~TestScene()
{
}

void
testGame::TestScene::update()
{
	std::cout << "component 1 value: " << ++_entity->getComponent<engine::TestComponent>().value << std::endl;
	std::cout << "component 2 value: " << --_entity2->getComponent<engine::TestComponent>().value << std::endl;

}
