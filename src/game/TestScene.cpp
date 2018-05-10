/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include <iostream>
#include "TestScene.hpp"
#include "engine/core/Game.hpp"
#include "engine/components/TestComponent.hpp"
#include "engine/components/DisplayComponent.hpp"

testGame::TestScene::TestScene(engine::Game* game) : engine::Scene(game)
{
	this->registerModel("test", [](engine::Entity const& entity) -> engine::Entity const& {
		engine::TestComponent& testComponent = entity.addComponent<engine::TestComponent>();
		testComponent.value = 42;
		return entity;
	});

	this->registerModel("map", [&](engine::Entity const& e) -> engine::Entity const& {
		auto& displayComponent = e.addComponent<engine::DisplayComponent>();
		displayComponent.init(game, "plant.md3");
		return e;
	});

	this->spawnEntity("map");

	_entity = this->spawnEntity("test");
	_entity2 = this->spawnEntity("test");
}

testGame::TestScene::~TestScene()
{
}

void
testGame::TestScene::update()
{
	std::cout << "component 1 value: " << ++(this->getEntity(_entity).getComponent<engine::TestComponent>().value) << std::endl;

}
