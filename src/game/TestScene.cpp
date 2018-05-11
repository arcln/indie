/*
** EPITECH PROJECT, 2017
** bomberman
** File description:
** A file for bomberman - Paul Laffitte
*/

#include <iostream>
#include "TestScene.hpp"

testGame::TestScene::TestScene(engine::Game* game) : engine::Scene()
{
	this->registerEntityModel("map", [&](engine::Entity const& entity) -> engine::Entity const& {
		auto& displayComponent = entity.addComponent<engine::DisplayComponent>();
		displayComponent.init(game, "plant.md3");
		return entity;
	});

	this->spawnEntity("map");
}

testGame::TestScene::~TestScene()
{
}
