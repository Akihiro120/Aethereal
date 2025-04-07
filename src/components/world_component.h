#pragma once
#include <glm/glm.hpp>
#include "render_component.h"

struct Tile {
	Render render;	
	bool collidable = false;
};

struct Chunk {
	std::vector<Tile> tiles;
};

struct World {
	std::unordered_map<int, Chunk> chunks;
	int chunk_size = 16;
	int seed = 1234;
};
