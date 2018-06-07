/*
** EPITECH PROJECT, 2017
** cpp_d0
** File description:
** Map
*/

#pragma once

#include "engine/core/Game.hpp"
#include "engine/core/Scene.hpp"
#include "engine/core/Entity.hpp"
#include "engine/components/IrrlichtComponent.hpp"
#include "engine/components/TransformComponent.hpp"
#include "Bsq.hpp"

namespace Wornite {

class Map {
public:
	Map() = default;
	~Map() = default;

	enum mapSize{
		SMALL,
		MEDIUM,
		LARGE
	};

	struct 	Settings
	{
		int 	Size;
		float 	Density;
	};

	typedef struct 		chunk
	{
		std::string 	string;
		int 		length;
		int 		height;
		int 		mapLength;
		int 		id;
		int 		nbChunks;
	}			chunk;

	typedef struct 		mapSettings
	{
		std::string 		string;
		int 			length;
		int 			height;
		std::vector<Wornite::Map::chunk> chunks;
		int 			nbChunks;
	}			mapSettings;

	void genMap(engine::Game* game, engine::Scene* scene, Settings* mapSettings);

private:
	int _blockDisplayed = 0;

	const float _mapPrecision = .2f;

	const char _grad3[12][3] = {
		{1, 1, 0}, {-1, 1, 0}, {1, -1, 0}, {-1, -1, 0},
		{1, 0, 1}, {-1, 0, 1}, {1, 0, -1}, {-1, 0, -1},
		{0, 1, 1}, {0, -1, 1}, {0, 1, -1}, {0, -1, -1}

	};

	const unsigned char _perm[512] = {
		182, 232, 51, 15, 55, 119, 7, 107, 230, 227, 6, 34, 216, 61, 183, 36,
		40, 134, 74, 45, 157, 78, 81, 114, 145, 9, 209, 189, 147, 58, 126, 0,
		240, 169, 228, 235, 67, 198, 72, 64, 88, 98, 129, 194, 99, 71, 30, 127,
		18, 150, 155, 179, 132, 62, 116, 200, 251, 178, 32, 140, 130, 139, 250, 26,
		151, 203, 106, 123, 53, 255, 75, 254, 86, 234, 223, 19, 199, 244, 241, 1,
		172, 70, 24, 97, 196, 10, 90, 246, 252, 68, 84, 161, 236, 205, 80, 91,
		233, 225, 164, 217, 239, 220, 20, 46, 204, 35, 31, 175, 154, 17, 133, 117,
		73, 224, 125, 65, 77, 173, 3, 2, 242, 221, 120, 218, 56, 190, 166, 11,
		138, 208, 231, 50, 135, 109, 213, 187, 152, 201, 47, 168, 185, 186, 167, 165,
		102, 153, 156, 49, 202, 69, 195, 92, 21, 229, 63, 104, 197, 136, 148, 94,
		171, 93, 59, 149, 23, 144, 160, 57, 76, 141, 96, 158, 163, 219, 237, 113,
		206, 181, 112, 111, 191, 137, 207, 215, 13, 83, 238, 249, 100, 131, 118, 243,
		162, 248, 43, 66, 226, 27, 211, 95, 214, 105, 108, 101, 170, 128, 210, 87,
		38, 44, 174, 188, 176, 39, 14, 143, 159, 16, 124, 222, 33, 247, 37, 245,
		8, 4, 22, 82, 110, 180, 184, 12, 25, 5, 193, 41, 85, 177, 192, 253,
		79, 29, 115, 103, 142, 146, 52, 48, 89, 54, 121, 212, 122, 60, 28, 42,
		182, 232, 51, 15, 55, 119, 7, 107, 230, 227, 6, 34, 216, 61, 183, 36,
		40, 134, 74, 45, 157, 78, 81, 114, 145, 9, 209, 189, 147, 58, 126, 0,
		240, 169, 228, 235, 67, 198, 72, 64, 88, 98, 129, 194, 99, 71, 30, 127,
		18, 150, 155, 179, 132, 62, 116, 200, 251, 178, 32, 140, 130, 139, 250, 26,
		151, 203, 106, 123, 53, 255, 75, 254, 86, 234, 223, 19, 199, 244, 241, 1,
		172, 70, 24, 97, 196, 10, 90, 246, 252, 68, 84, 161, 236, 205, 80, 91,
		233, 225, 164, 217, 239, 220, 20, 46, 204, 35, 31, 175, 154, 17, 133, 117,
		73, 224, 125, 65, 77, 173, 3, 2, 242, 221, 120, 218, 56, 190, 166, 11,
		138, 208, 231, 50, 135, 109, 213, 187, 152, 201, 47, 168, 185, 186, 167, 165,
		102, 153, 156, 49, 202, 69, 195, 92, 21, 229, 63, 104, 197, 136, 148, 94,
		171, 93, 59, 149, 23, 144, 160, 57, 76, 141, 96, 158, 163, 219, 237, 113,
		206, 181, 112, 111, 191, 137, 207, 215, 13, 83, 238, 249, 100, 131, 118, 243,
		162, 248, 43, 66, 226, 27, 211, 95, 214, 105, 108, 101, 170, 128, 210, 87,
		38, 44, 174, 188, 176, 39, 14, 143, 159, 16, 124, 222, 33, 247, 37, 245,
		8, 4, 22, 82, 110, 180, 184, 12, 25, 5, 193, 41, 85, 177, 192, 253,
		79, 29, 115, 103, 142, 146, 52, 48, 89, 54, 121, 212, 122, 60, 28, 42
	};

	float __attribute__ ((pure))	dot3(const char a[], float x, float y, float z);
	float __attribute__ ((const))	lerp(float a, float b, float t);
	float __attribute__ ((const))	fade(float n);
	float __attribute__((pure))	getPerlin2(unsigned int gi[8], irr::core::vector3df r, irr::core::vector3df f);
	float __attribute__((pure)) getPerlin(float x, float y, float z);
	void fillBigChunks(engine::Game* game, engine::Scene* scene,
			   chunk *map);

	void spawnBigChunk(engine::Game* game, engine::Scene* scene,
			   Bsq::t_map *map, Bsq::t_response *res, chunk *chunk);

	void spawnPieceMap(engine::Game* game, engine::Scene* scene,
			   irr::core::vector3df position, irr::core::vector3df scale);

	void removeBigChunk(Bsq::t_map *map, Bsq::t_response *res);

	void getChunk(mapSettings *map);

	void spawnChunkHitbox(engine::Game *pGame, engine::Scene *pScene, chunk *pChunk);
};

}
