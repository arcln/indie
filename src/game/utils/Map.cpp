/*
** EPITECH PROJECT, 2017
** cpp_d0
** File description:
** Map
*/

#include "Map.hpp"

void
Wornite::Map::spawnMap(engine::Game *game, engine::Scene *scene, Wornite::Map::Settings *mapSettings)
{
	irr::core::vector3df position;
	position.X = 0;
	position.Y = 0;
	position.Z = 0;

	scene->registerEntityModel("pieceMap", [&](engine::Entity const& entity) {
		auto& IrrlichtComponent = entity.set<engine::IrrlichtComponent>(game, "obj/pieceMap.obj");
		IrrlichtComponent.node->setMaterialTexture(0, game->textureManager.get("texture/map.png"));

		auto& TransformComponent = entity.set<engine::TransformComponent>();
		TransformComponent.position = position;
	});
	scene->spawnEntity("pieceMap");
}
