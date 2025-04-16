#pragma once
#include <glm/glm.hpp>
#include "render_component.h"
#include "tags.h"

namespace std {
	template <>
	struct hash<glm::ivec2> {
		std::size_t operator()(const glm::ivec2& v) const noexcept {
			return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
		}
	};
}

struct Tile {
	RenderComponent render;	
    std::vector<Tag> tags;
    std::string tile_obj_id = "";
    int yield = 1;
	bool collidable = false;
};

struct Chunk {
	std::vector<Tile> tiles;
};

struct WorldComponent {
	std::unordered_map<glm::ivec2, Chunk, std::hash<glm::ivec2>> chunks;
	glm::ivec2 chunk_size = { 8, 8 };
	int seed = 1234;
};
