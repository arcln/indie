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
	this->registerModel("map", [&](engine::Entity const& e) -> engine::Entity const& {
		auto& displayComponent = e.addComponent<engine::DisplayComponent>();
		displayComponent.init(game, "plant.md3");
		return e;
	});

	this->spawnEntity("map");
}

testGame::TestScene::~TestScene()
{
}

void
testGame::TestScene::update()
{}
