/*
** EPITECH PROJECT, 2017
** cpp_d0
** File description:
** Map
*/

#include "Map.hpp"
#include "Bsq.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <engine/components/HitboxComponent.hpp>




void
Wornite::Map::genMap(engine::Game *game, engine::Scene *scene, Wornite::Map::Settings *settings)
{
	float perlinScale;
	mapSettings map;

	std::srand(static_cast<unsigned>(std::time(0)));
	perlinScale = std::rand() % 1000;
	switch (settings->Size) {
		case mapSize::SMALL : map.mapLength = 80;
			map.mapHeight = 25;
			break;
		case mapSize::MEDIUM : map.mapLength = 100;
			map.mapHeight = 33;
			break;
		case mapSize::LARGE : map.mapLength = 120;
			map.mapHeight = 40;
			break;
	}
	for (float y = -(map.mapLength / 2.f); y < map.mapLength / 2.f; y += _mapPrecision) {
		for (float x = -(map.mapLength / 2.f); x < map.mapLength / 2.f; x += _mapPrecision) {
			irr::core::vector3df position;
			float perlin;
			perlin = getPerlin((x + perlinScale) / 100.f * 10.f,
					   (y + perlinScale) / 100.f * 10.F,
					   0);
			if ((y > -(map.mapHeight / 2.f) && y < map.mapHeight / 2.f && perlin < (settings->Density) * 0.2f - 0.2)
			    || (y > map.mapHeight / 2.f && y < map.mapHeight / 2.f + 5))
				map.mapString.push_back('.');
			else
				map.mapString.push_back('o');
		}
		map.mapString.push_back('\n');
	}

	replaceBigChunks(game, scene, &map);
	printf("block displayed: %d\n", _blockDisplayed);
}

void Wornite::Map::replaceBigChunks(engine::Game *game, engine::Scene *scene, Wornite::Map::mapSettings *map)
{
	Bsq bsq;
	Bsq::t_response res = {{0,0}, 99};
	Bsq::t_map mapBsq;

	mapBsq.dots = ::strdup(map->mapString.c_str());
	mapBsq.row = (unsigned int) std::count(map->mapString.begin(), map->mapString.end(), '\n');
	mapBsq.col = (unsigned int) map->mapString.find_first_of('\n', 0);
	bsq.find_bsq(&mapBsq, &res);
	while (res.size > 1) {
		spawnBigChunk(game, scene, &mapBsq, &res);
		bsq.find_bsq(&mapBsq, &res);
	}

	map->mapString = mapBsq.dots;
	spawnMap(game, scene, map);
	delete mapBsq.dots;
}

void
Wornite::Map::spawnBigChunk(engine::Game *game, engine::Scene *scene,
			    Wornite::Bsq::t_map *map, Wornite::Bsq::t_response *res)
{
	irr::core::vector3df position;
	irr::core::vector3df scale;

	position.X = (res->pos.x * _mapPrecision) + (res->size / 2.f * _mapPrecision) - (map->col / 2.f * _mapPrecision);
	position.Y = -((res->pos.y * _mapPrecision + res->size * _mapPrecision / 2.f) - (map->row * _mapPrecision / 2.f));
	position.Z = 0.f;
	scale.X = res->size / 2.f * _mapPrecision;
	scale.Y = res->size / 2.f * _mapPrecision;
	scale.Z = 1.f;
	spawnPieceMap(game, scene, position, scale);
	removeBigChunk(map, res);
}

void
Wornite::Map::removeBigChunk(Wornite::Bsq::t_map *map, Wornite::Bsq::t_response *res)
{
	irr::core::vector3di cur;

	cur.Y = res->pos.y + res->size - 1;
	while (cur.Y != res->pos.y - 1)
	{
		cur.X = res->pos.x + res->size - 1;
		while (cur.X != res->pos.x - 1)
		{
			map->dots[(cur.X + (cur.Y * (map->row + 1)))] = 'o';
			cur.X -= 1;
		}
		cur.Y -= 1;
	}
}

void
Wornite::Map::spawnMap(engine::Game *game, engine::Scene *scene, Wornite::Map::mapSettings *map)
{
	for (int y = 0; y < map->mapHeight; y += 1) {
		for (int x = 0; x < map->mapLength; x += 1) {
			irr::core::vector3df position = {-(map->mapLength / 2.f * _mapPrecision) + ((x + 0.5f) * _mapPrecision),
											 -(map->mapHeight * _mapPrecision / 2.f) + ((y + 0.5f) * _mapPrecision), 0};
			irr::core::vector3df scale = {_mapPrecision, _mapPrecision, _mapPrecision};

			if (map->mapString[y * (map->mapLength + 1) + x] == '.') {
				position.Y = -position.Y;
				spawnPieceMap(game, scene, position, scale);
			}
		}
	}
}

void
Wornite::Map::spawnPieceMap(engine::Game *game, engine::Scene *scene,
			    irr::core::vector3df position,
			    irr::core::vector3df scale)
{
	scene->registerEntityModel("pieceMap", [&](engine::Entity const &entity) {
		auto &irrlichtComponent = entity.set<engine::IrrlichtComponent>(game,
										"obj/pieceMap.obj");
		irrlichtComponent.node->setMaterialTexture(0, game->textureManager.get("texture/map.png"));
		entity.set<engine::TransformComponent>();
//		auto &hitboxComponent = entity.set<engine::HitboxComponent>("(-1 -0.5, -1 0.5, 1 0.5, 1 -0.5)");
//		hitboxComponent.hasDebugMode = true;
	});

	auto& t = scene->spawnEntity("pieceMap").get<engine::TransformComponent>();
	t.position = position;
	t.scale = scale;

	_blockDisplayed += 1;
}

float __attribute__ ((pure))
Wornite::Map::dot3(const char a[], float x, float y, float z)
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
	unsigned int			gi[8];
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
