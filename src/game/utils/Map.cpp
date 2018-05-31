/*
** EPITECH PROJECT, 2017
** cpp_d0
** File description:
** Map
*/

#include "Map.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>




void
Wornite::Map::spawnMap(engine::Game *game, engine::Scene *scene, Wornite::Map::Settings *mapSettings)
{
	float perlinScale;
	int mapLength;
	int mapHeight;

	srand (static_cast <unsigned> (time(0)));
	perlinScale = rand() % 1000;
	switch (mapSettings->Size) {
		case mapSize::SMALL : mapLength = 60;
			mapHeight = 30;
			break;
		case mapSize::MEDIUM : mapLength = 80;
			mapHeight = 40;
			break;
		case mapSize::LARGE : mapLength = 100;
			mapHeight = 45;
			break;
	}
	for (float y = -mapLength; y < mapLength; y += _mapPrecision) {
		for (float x = -(mapHeight / 2.); x < mapHeight / 2.; x += _mapPrecision) {
			irr::core::vector3df position;
			float perlin;

			position.X = y;
			position.Y = x;
			position.Z = 0;
			perlin = getPerlin((position.X + perlinScale) / 100.f * 10.f,
					   (position.Y + perlinScale) / 100.f * 10.F,
					   position.Z);
			if (perlin < -0.1f)
				continue;
			scene->registerEntityModel("pieceMap", [&](engine::Entity const &entity) {
				auto &IrrlichtComponent = entity.set<engine::IrrlichtComponent>(game,
												"obj/pieceMap.obj");
				IrrlichtComponent.node->setMaterialTexture(0, game->textureManager.get(
					"texture/map.png"));

				auto &TransformComponent = entity.set<engine::TransformComponent>();
				TransformComponent.position = position;
				TransformComponent.scale = {0.2f, 0.2f, 1.f};
			});
			scene->spawnEntity("pieceMap");
		}
	}
}

float __attribute__ ((pure))
Wornite::Map::dot3(const char a[],
						float x,
						float y,
						float z)
{
	return (a[0] * x + a[1] * y + a[2] * z);
}

float __attribute__ ((const))
Wornite::Map::lerp(float a, float b, float t)
{
	return ((1 - t) * a + t * b);
}

float __attribute__ ((const))
Wornite::Map::fade(float n)
{
	return (n * n * n * (n * (n * 6 - 15) + 10));
}

float __attribute__((pure))
Wornite::Map::getPerlin2(unsigned int gi[8],
			 irr::core::vector3df r, irr::core::vector3df f)
{
	float				n[8];
	float				nx[4];
	float				nxy[2];
	int				index;

	index = -1;
	while (++index != 8)
		n[index] = dot3(_grad3[gi[index]], r.X - ((index >> 2) & 1),
				r.Y - ((index >> 1) & 1), r.Z - (index & 1));
	f.X = fade(r.X);
	f.Y = fade(r.Y);
	f.Z = fade(r.Z);
	index = -1;
	while (++index != 4)
		nx[index] = lerp(n[index], n[4 + index], f.X);
	index = -1;
	while (++index != 2)
		nxy[index] = lerp(nx[index], nx[2 + index], f.Y);
	return (lerp(nxy[0], nxy[1], f.Z));
}

float __attribute__((pure))
Wornite::Map::getPerlin(float x, float y, float z)
{
	irr::core::vector3df 	g;
	irr::core::vector3df 	r;
	irr::core::vector3df 	f;
	unsigned int		gi[8];
	int			index;

	g.X = std::floor(x);
	g.Y = std::floor(y);
	g.Z = std::floor(z);
	r.X = x - g.X;
	r.Y = y - g.Y;
	r.Z = z - g.Z;
	g.X = (int)g.X & 255;
	g.Y = (int)g.Y & 255;
	g.Z = (int)g.Z & 255;
	index = -1;
	while (++index != 8)
		gi[index] = _perm[(int)g.X + ((index >> 2) & 1) +
				   _perm[(int)g.Y + ((index >> 1) & 1) +
					  _perm[(int)g.Z + (index & 1)]]] % 12;
	return (getPerlin2(gi, r, f));
}
