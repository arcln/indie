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
#include "engine/components/HitboxComponent.hpp"
#include "engine/components/TagComponent.hpp"
#include "engine/components/PhysicsComponent.hpp"
#include "engine/core/Entities.hpp"
#include "engine/helpers/GeometryHelper.hpp"

void
Wornite::Map::genMap(engine::Game& game, engine::Scene &scene)
{
	float perlinScale;
	mapSettings map;

	scene.registerEntityModel("hitboxChunk", [&](engine::Entity const &entity) {
		entity.set<engine::TransformComponent>();
		entity.set<engine::TagComponent>(std::string("map"));
	});
	scene.registerEntityModel("hitboxBlast", [&](engine::Entity const &entity) {
		entity.set<engine::TransformComponent>();
	});
	scene.registerEntityModel("pieceMap", [&](engine::Entity const &entity) {
		auto &irrlichtComponent = entity.set<engine::IrrlichtComponent>(&game, "obj/cube.obj", "texture/cube.png");
		entity.set<engine::TransformComponent>();

		irrlichtComponent.node->setMaterialFlag(irr::video::EMF_TEXTURE_WRAP, false);
	});
	std::srand(static_cast<unsigned>(std::time(0)));
	perlinScale = std::rand() % 1000;
	map.length = 70;
	map.height = 25;
	for (float y = 0.f; y < map.length; y += _mapPrecision) {
		float perlinY = ((y > map.length * 0.8f ? map.length * 0.8f : y) / (map.length * 0.8f));
		for (float x = 0.f; x < map.length; x += _mapPrecision) {
			float perlin;

			perlin = (((getPerlin((x + perlinScale) / 6.f,
					   (y + perlinScale) / 6.f,
					   0) + 1.f) / 6.7f));
			perlin = perlin + perlinY;
			if (perlin > 0.7f && y < map.length - map.height * 1.2)
				map.string.push_back('.');
			else
				map.string.push_back('o');
		}
		map.string.push_back('\n');
	}
	getChunk(&map);
	for (int i = 0; i < map.nbChunks; i++) {
		fillBigChunks(game, scene, &map.chunks[i]);
	}
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
		chunk chunk = {"", map->length / map->nbChunks, map->height, map->length, i, map->nbChunks, engine::Entity()};
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

void Wornite::Map::fillBigChunks(engine::Game& game, engine::Scene& scene, chunk *chunk)
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
	spawnChunkHitbox(scene, chunk);
	bsq.find_bsq(&mapBsq, &res);
	while (res.size > 0) {
		spawnBigChunk(scene, &mapBsq, &res, chunk);
		bsq.find_bsq(&mapBsq, &res);
	}
	chunk->string = std::string(mapBsq.dots);
	delete mapBsq.dots;
}


void
Wornite::Map::spawnBigChunk(engine::Scene& scene,
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
	Wornite::Map::spawnPieceMap(scene, position, scale, chunk->chunkHitboxEntity);
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
Wornite::Map::spawnPieceMap(engine::Scene &scene, irr::core::vector3df position, irr::core::vector3df scale,
			    engine::Entity hitboxEntity)
{
	auto const& entity = scene.spawnEntity("pieceMap");
	auto& transform = entity.get<engine::TransformComponent>();

	transform.position = position;
	transform.scale = scale;
    auto& h = entity.set<engine::HitboxComponent>("(-1 -1, -1 1, 1 1, 1 -1)");
	h.hasDebugMode = true;
	h.isStatic = true;
    engine::GeometryHelper::transformHitbox(h, transform);
	hitboxEntity.attach(entity);
}


void
Wornite::Map::spawnChunkHitbox(engine::Scene& scene,
			       Wornite::Map::chunk *chunk)
{
	std::string hitbox("( ");

	hitbox += std::to_string((0.f * _mapPrecision) - (chunk->length / 2.f * _mapPrecision)) + " " +
		     std::to_string((chunk->height / 2.f * _mapPrecision)) + ", ";
	hitbox += std::to_string((chunk->length * _mapPrecision) - (chunk->length / 2.f * _mapPrecision)) + " " +
		  std::to_string((chunk->height / 2.f * _mapPrecision)) + ", ";
	hitbox += std::to_string((chunk->length * _mapPrecision) - (chunk->length / 2.f * _mapPrecision)) + " " +
		  std::to_string(- (chunk->height / 2.f * _mapPrecision)) + ", ";
	hitbox += std::to_string( - (chunk->length * _mapPrecision / 2.f)) + " " +
		     std::to_string(-(chunk->height / 2.f * _mapPrecision)) + ")";
	spawnHitbox(scene, chunk, hitbox);
}


void
Wornite::Map::spawnHitbox(engine::Scene& scene, chunk *chunk, std::string hitbox)
{
	auto const& hitboxEntity = scene.spawnEntity("hitboxChunk");
	auto& transformComponent = hitboxEntity.get<engine::TransformComponent>();
	transformComponent.position = {(chunk->length / 2.f * _mapPrecision) + ((chunk->id * chunk->length * _mapPrecision) - (chunk->mapLength / 2.f * _mapPrecision)),
				       0.f,
					0.f};
	transformComponent.scale = {1.f, 1.f, 1.f};
	auto& hitboxComponent = hitboxEntity.set<engine::HitboxComponent>(hitbox);
	hitboxComponent.hasDebugMode = true;
	hitboxComponent.isAABBOnly = true;
	hitboxComponent.isStatic = true;
    	engine::GeometryHelper::transformHitbox(hitboxComponent, transformComponent);
	chunk->chunkHitboxEntity = hitboxEntity;
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

void
Wornite::Map::divideBlock(engine::Scene& scene, engine::Entity entity)
{
	engine::Entity parent;
	float entitySize;

	parent = entity.getEntities()->getParentEntity(entity);
	auto& t = entity.get<engine::TransformComponent>();
	irr::core::vector3df position;
	irr::core::vector3df scale;

	entitySize = t.scale.X / 2.f;
	scale.X = entitySize;
	scale.Y = entitySize;
	scale.Z = 1.f;

//	std::cout << "x: " << t.position.X << " y: " << t.position.Y << " size : " << t.scale.X << std::endl;

//	std::cout << "scale : " << t.scale.X << std::endl;
//	entitySize = t.scale.X / 0.1f;
//	scale.X = 0.1f;
//	scale.Y = 0.1f;
//	scale.Z = 1.f;
//	for (float y = 0.f; y < entitySize; y += scale.Y) {
//		for (float x = 0.f; x < entitySize; x += scale.X) {
//			position.X = t.position.X + x - (entitySize * 0.1f / 2.f);
//			position.Y = t.position.Y - y - (entitySize * 0.1f / 2.f);
//			position.Z = t.position.Z;
//
//			Wornite::Map::spawnPieceMap(scene, position, scale, parent);
//		}
//	}
//
//	entity.kill();

	position.X = t.position.X - entitySize;
	position.Y = t.position.Y + entitySize;
	position.Z = t.position.Z;
	Wornite::Map::spawnPieceMap(scene, position, scale, parent);
	position.X = t.position.X + entitySize;
	position.Y = t.position.Y + entitySize;
	Wornite::Map::spawnPieceMap(scene, position, scale, parent);
	position.X = t.position.X + entitySize;
	position.Y = t.position.Y - entitySize;
	Wornite::Map::spawnPieceMap(scene, position, scale, parent);
	position.X = t.position.X - entitySize;
	position.Y = t.position.Y - entitySize;
	Wornite::Map::spawnPieceMap(scene, position, scale, parent);
	entity.kill();
}

std::vector<engine::Entity>
Wornite::Map::getBlastCollision(engine::Entities& entities, engine::Entity blastHitbox)
{
	std::vector<engine::Entity> blastCollision;

	entities.withTag("map", [&](engine::Entity const& chunk) {
		if (engine::GeometryHelper::AABBCollide(chunk.get<engine::HitboxComponent>(), blastHitbox.get<engine::HitboxComponent>())) {

			entities.eachChilds(chunk.getId(), [&](engine::Entity const &child) {
				if (engine::GeometryHelper::simplePolygonCollide(child, blastHitbox)) {
					auto &t = child.get<engine::TransformComponent>();

					if (ceil(t.scale.X * 10.f) / 10.f <= 0.1f) {
						child.kill();
					} else {
						blastCollision.push_back(child);
					}
				}
			});
		}
	});

	return blastCollision;
}

void Wornite::Map::tryDestroyMap(engine::Scene& scene, float x, float y, float radius)
{
	engine::Entity blast = engine::GeometryHelper::createBlastPolygon(scene, x, y, radius);
    auto& bt = blast.get<engine::TransformComponent>();
	std::vector<engine::Entity> blockToDivide = getBlastCollision(scene.getEntities(), blast);

    scene.getEntities().each<engine::PhysicsComponent, engine::TransformComponent>([&](engine::Entity const& e, auto& p, auto& t) {
        if (!engine::GeometryHelper::simplePolygonCollide(e, blast))
            return;
        engine::Vec2D vec;
        vec.X = t.position.X - bt.position.X;
        vec.Y = t.position.Y - bt.position.Y + 100.f;
        vec.normalize();
        vec *= radius * 50.f;
        p.velocity += vec;
    });

	while (!blockToDivide.empty()) {
		for (unsigned int idx = 0; idx < blockToDivide.size(); idx++) {
			divideBlock(scene, blockToDivide[idx]);
		}
		blockToDivide = getBlastCollision(scene.getEntities(), blast);
	}
	blockToDivide = getBlastCollision(scene.getEntities(), blast);
	for (unsigned int idx = 0; idx < blockToDivide.size(); idx++) {
		blockToDivide[idx].kill();
	}

	blast.kill();
}
