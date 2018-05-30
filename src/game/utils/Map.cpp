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
	int length;

	switch (mapSettings->Size) {
		case SMALL : length = 25;
		case MEDIUM : length = 40;
		case LARGE : length = 60;
	}
	for (int y = -(length / 2); y < length / 2; y++) {
		for (int x = -(length / 2); x < length / 2; x++) {
			irr::core::vector3df position;

			position.X = x;
			position.Y = y;
			position.Z = 0;
			scene->registerEntityModel("pieceMap", [&](engine::Entity const& entity) {
				auto& IrrlichtComponent = entity.set<engine::IrrlichtComponent>(game, "obj/pieceMap.obj");
				IrrlichtComponent.node->setMaterialTexture(0, game->textureManager.get("texture/map.png"));

				auto& TransformComponent = entity.set<engine::TransformComponent>();
				TransformComponent.position = position;
			});
			scene->spawnEntity("pieceMap");
		}
	}
}
