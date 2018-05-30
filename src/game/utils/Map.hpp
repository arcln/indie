/*
** EPITECH PROJECT, 2017
** cpp_d0
** File description:
** Map
*/

#pragma once

#include <engine/core/Game.hpp>
#include "engine/core/Scene.hpp"
#include "engine/core/Entity.hpp"
#include "engine/components/IrrlichtComponent.hpp"
#include "engine/components/TransformComponent.hpp"

namespace Wornite {

class Map {
public:
	Map() = default;
	~Map() = default;

	enum {
		SMALL,
		MEDUIM,
		BIG
	};

	struct 	Settings
	{
		int 	Size;
		int 	Density;
	};

	void spawnMap(engine::Game* game, engine::Scene* scene, Settings* map);

private:
};

}