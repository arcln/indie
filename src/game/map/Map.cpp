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
		case mapSize::SMALL : map.length = 70;
			map.height = 25;
			break;
		case mapSize::MEDIUM : map.length = 100;
			map.height = 33;
			break;
		case mapSize::LARGE : map.length = 120;
			map.height = 40;
			break;
		default: map.length = 70;
			map.height = 25;
			break;
	}
	for (float y = 0.f; y < map.length; y += _mapPrecision) {
		float perlinY = ((y > map.length * 0.8f ? map.length * 0.8f : y) / (map.length * 0.8f));
		for (float x = 0.f; x < map.length; x += _mapPrecision) {
			irr::core::vector3df position;
			float perlin;

			perlin = (((getPerlin((x + perlinScale) / 6.f,
					   (y + perlinScale) / 6.f,
					   0) + 1.f) / 6.7f));
			perlin = perlin + perlinY;
			if (perlin > 0.70f && y < map.length - map.height * 1.2)
				map.string.push_back('.');
			else
				map.string.push_back('o');
		}
		map.string.push_back('\n');
	}
	getChunk(&map);
	for (int i = 0; i < map.nbChunks; i++) {
		std::cout << map.chunks[i].string << std::endl;
		fillBigChunks(game, scene, &map.chunks[i]);
	}
	printf("block displayed: %d\n", _blockDisplayed);
}

void
Wornite::Map::getChunk(Wornite::Map::mapSettings *map)
{
	float y0 = 0.f;

	for (float y = 0.f; y < map->length / _mapPrecision; y += 1) {
		for (float x = 0.f; x < map->length / _mapPrecision; x += 1) {
			if (map->string[x + y * (map->length / _mapPrecision + 1)] == '.') {
				y0 = y;
				break;
			}
		}
		if (y0 != 0.f)
			break;
	}


	map->height = int(((map->length - map->height * 1.2) / _mapPrecision) - y0);
	map->length = int(map->length / _mapPrecision);
	map->nbChunks = (int) std::ceil(static_cast<float>(map->length) / static_cast<float>(map->height));

	for (int i = 0; i < map->nbChunks; i++) {
		chunk chunk = {"", map->length / map->nbChunks, map->height, map->length, i, map->nbChunks};
		map->chunks.push_back(chunk);
	}

	for (float y = y0; y < y0 + map->height; y += 1.f) {
		for (float x = 0.f; x < map->nbChunks * map->height; x += 1.f) {
			if (x >= map->length) {
				map->chunks[std::floor(x / static_cast<float>(map->height))].string.push_back('o');
			} else {
				map->chunks[std::floor(x / static_cast<float>(map->height))].string.push_back(map->string[x + y * (map->length + 1)]);
			}
		}
		for (int i = 0; i < map->nbChunks; i++) {
			map->chunks[i].string.push_back('\n');
		}
	}
}

void Wornite::Map::fillBigChunks(engine::Game *game, engine::Scene *scene, chunk *chunk)
{
	Bsq bsq;
	Bsq::t_response res = {{0,0}, 99};
	Bsq::t_map mapBsq;
	engine::Entity hitboxEntity;

	mapBsq.dots = ::strdup(chunk->string.c_str());
	mapBsq.row = (unsigned int) std::count(chunk->string.begin(), chunk->string.end(), '\n');
	mapBsq.col = (unsigned int) chunk->string.find_first_of('\n', 0);
	chunk->length = mapBsq.row;
	chunk->height = mapBsq.col;
	chunk->chunkHitboxEntity = spawnChunkHitbox(game, scene, chunk);
	bsq.find_bsq(&mapBsq, &res);
	while (res.size > 0) {
		spawnBigChunk(game, scene, &mapBsq, &res, chunk);
		bsq.find_bsq(&mapBsq, &res);
	}

	chunk->string = std::string(mapBsq.dots);
	delete mapBsq.dots;
}


void
Wornite::Map::spawnBigChunk(engine::Game *game, engine::Scene *scene,
			    Wornite::Bsq::t_map *map, Wornite::Bsq::t_response *res, chunk *chunk)
{
	irr::core::vector3df position;
	irr::core::vector3df scale;

	position.X = (res->pos.x * _mapPrecision) + (res->size / 2.f * _mapPrecision)
		     + ((chunk->id * map->col * _mapPrecision) - (chunk->mapLength / 2.f * _mapPrecision));
	position.Y = -((res->pos.y * _mapPrecision + res->size * _mapPrecision / 2.f) - (map->row * _mapPrecision / 2.f));
	position.Z = 0.f;
	scale.X = res->size / 2.f * _mapPrecision;
	scale.Y = res->size / 2.f * _mapPrecision;
	scale.Z = 1.f;
	spawnPieceMap(game, scene, position, scale, chunk->chunkHitboxEntity);
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
Wornite::Map::spawnPieceMap(engine::Game *game, engine::Scene *scene, irr::core::vector3df position, irr::core::vector3df scale,
			    engine::Entity hitboxEntity)
{
	scene->registerEntityModel("pieceMap", [&](engine::Entity const &entity) {
		auto &irrlichtComponent = entity.set<engine::IrrlichtComponent>(game,
										"obj/pieceMap.obj");
		irrlichtComponent.node->setMaterialTexture(0, game->textureManager.get("texture/map.png"));
		entity.set<engine::TransformComponent>();
	});

	auto const& entity = scene->spawnEntity("pieceMap");
    auto& transform = entity.get<engine::TransformComponent>();
	transform.position = position;
	transform.scale = scale;
    auto& h = entity.set<engine::HitboxComponent>("(-1 -1, -1 1, 1 1, 1 -1)");
//	h.hasDebugMode = true;
	hitboxEntity.attach(entity);
	_blockDisplayed += 1;
}


const engine::Entity &
Wornite::Map::spawnChunkHitbox(engine::Game *game, engine::Scene *scene,
			       Wornite::Map::chunk *chunk)
{
	std::string hitbox("( ");
//	irr::core::vector2df node;
//
//	for (float y = 0.f; y < chunk->height; y += 1.f) {
////		std::cout << "chunk [" << y * (chunk->length + 1.f) << "] : " << chunk->string[y * (chunk->length + 1.f)] << std::endl;
//		if (chunk->string[y * (chunk->length + 1.f)] == '.') {
//
//			node.X = 0;
//			node.Y = y;
//			hitbox += std::to_string(-(chunk->length / 2.f * _mapPrecision)) + ' ' +
//				std::to_string(-(y * _mapPrecision) + (chunk->height * _mapPrecision / 2.f)) + ", ";
//			break;
//		}
//	}
//	irr::core::vector2df nextNode =  {node.X, node.Y};
//
//	for (float x = 1.f; x < chunk->length; x += 1.f) {
//		getNextNode(nextNode.X, nextNode.Y, chunk, &nextNode);
////		std::cout << "node Y : " << nextNode.Y << " = " << -(nextNode.Y * _mapPrecision) << " - " << (chunk->height * _mapPrecision / 2.f) << std::endl;
//		hitbox += std::to_string((nextNode.X * _mapPrecision) - (chunk->length / 2.f * _mapPrecision) - (_mapPrecision / 2.f)) + ' ' +
//			std::to_string(-(nextNode.Y * _mapPrecision) + (chunk->height * _mapPrecision / 2.f) - (_mapPrecision / 2.f)) + ", ";
//	}

	hitbox += std::to_string((0.f * _mapPrecision) - (chunk->length / 2.f * _mapPrecision)) + " " +
		     std::to_string((chunk->height / 2.f * _mapPrecision)) + ", ";
	hitbox += std::to_string((chunk->length * _mapPrecision) - (chunk->length / 2.f * _mapPrecision)) + " " +
		  std::to_string((chunk->height / 2.f * _mapPrecision)) + ", ";
	hitbox += std::to_string((chunk->length * _mapPrecision) - (chunk->length / 2.f * _mapPrecision)) + " " +
		  std::to_string(- (chunk->height / 2.f * _mapPrecision)) + ", ";
	hitbox += std::to_string( - (chunk->length * _mapPrecision / 2.f)) + " " +
		     std::to_string(-(chunk->height / 2.f * _mapPrecision)) + ")";


//	getHitboxEdge(node, nextNode, chunk, &hitbox);
	return spawnHitbox(game, scene, chunk, hitbox);
}


const engine::Entity &
Wornite::Map::spawnHitbox(engine::Game *game, engine::Scene *scene, chunk *chunk, std::string hitbox)
{
	scene->registerEntityModel("hitboxChunk", [&](engine::Entity const &entity) {
		auto &irrlichtComponent = entity.set<engine::IrrlichtComponent>(game,
										"obj/pieceMap.obj");
		entity.set<engine::TransformComponent>();
	});

	auto const& hitboxEntity = scene->spawnEntity("hitboxChunk");
	auto& transformComponent = hitboxEntity.get<engine::TransformComponent>();
	transformComponent.position = {(chunk->length / 2.f * _mapPrecision) + ((chunk->id * chunk->length * _mapPrecision) - (chunk->mapLength / 2.f * _mapPrecision)),
				       0.f,
					0.f};
	transformComponent.scale = {1.f, 1.f, 1.f};
	auto& hitboxComponenet = hitboxEntity.set<engine::HitboxComponent>(hitbox);
	hitboxComponenet.hasDebugMode = true;

	return hitboxEntity;
}

void
Wornite::Map::getNextNode(irr::f32 x, irr::f32 y,
			  chunk *chunk, irr::core::vector2df *node)
{
	if (x <= chunk->length && y <= chunk->height) {
		if (isNextNode(x, y - 1.f, chunk)) {
			node->X = x;
			node->Y = y - 1.f;
		} else if (isNextNode(x + 1.f, y - 1.f, chunk)) {
			node->X = x + 1.f;
			node->Y = y - 1.f;
		} else if (isNextNode(x + 1.f, y, chunk)) {
			node->X = x + 1.f;
			node->Y = y;
		} else if (isNextNode(x + 1.f, y + 1.f, chunk)) {
			node->X = x + 1.f;
			node->Y = y + 1.f;
		} else if (isNextNode(x, y + 1.f, chunk)) {
			node->X = x;
			node->Y = y + 1.f;
		} else if (isNextNode(x - 1.f, y + 1.f, chunk)) {
			node->X = x - 1.f;
			node->Y = y + 1.f;
		} else if (isNextNode(x - 1.f, y - 1.f, chunk)) {
			node->X = x - 1.f;
			node->Y = y - 1.f;
		} else if (isNextNode(x - 1.f, y, chunk)) {
			node->X = x - 1.f;
			node->Y = y;
		} else if (isNextNode(x - 1.f, y + 1.f, chunk)) {
			node->X = x - 1.f;
			node->Y = y + 1.f;
		}
	} else {
		node->X = 0;
		node->Y = 0;
	}
}


void
Wornite::Map::getHitboxEdge(irr::core::vector2df last,
			    irr::core::vector2df first,
			    chunk *chunk,
			    std::string *hitbox)
{
	*(hitbox) += std::to_string((first.X * _mapPrecision) - (chunk->length / 2.f * _mapPrecision)) + " " +
		     std::to_string(-(chunk->height / 2.f * _mapPrecision)) + ", ";
	*(hitbox) += std::to_string(-(chunk->length * _mapPrecision / 2.f)) + " " +
		     std::to_string(-(chunk->height / 2.f * _mapPrecision)) + ")";
}


int
Wornite::Map::isNextNode(float x, float y, Wornite::Map::chunk *chunk)
{
	int neighbourNode = 0;

	if (chunk->string[x + 1 + (y * (chunk->length + 1))] == '.') {
		neighbourNode++;
	} if (chunk->string[x + ((y + 1) * (chunk->length + 1))] == '.') {
		neighbourNode++;
	} if (chunk->string[x + ((y - 1) * (chunk->length + 1))] == '.') {
		neighbourNode++;
	} if (chunk->string[x - 1 + (y * (chunk->length + 1))] == '.') {
		neighbourNode++;
	}
	if (neighbourNode > 1 && neighbourNode < 4)
		return 1;
	else
		return 0;
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
