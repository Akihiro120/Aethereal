#pragma once
#include <functional>
#include <glm/glm.hpp>
#include <unordered_map>
#include "../../../components/world_component.h"

namespace GameUtils {
    static void get_tile_world(WorldComponent& world, glm::vec2 pos, std::function<void(Tile* tile)> callback) {

        glm::ivec2 sel_pos = pos;
        glm::ivec2 pos_chunk = glm::floor(
            glm::vec2(
                sel_pos.x / (float)world.chunk_size.x,
                sel_pos.y / (float)world.chunk_size.y
            )
        );

        glm::ivec2 pos_tile = glm::ivec2(
            (sel_pos.x % world.chunk_size.x + world.chunk_size.x) % world.chunk_size.x,
            (sel_pos.y % world.chunk_size.y + world.chunk_size.y) % world.chunk_size.y
        );

        auto it = world.chunks.find(pos_chunk);
        if (it != world.chunks.end()) {
            // get the tiles
            int index = pos_tile.x + world.chunk_size.x * pos_tile.y;
            if (index >= 0 && index < it->second.tiles.size()) {

                callback(&it->second.tiles[index]);
            }
        }
    } 
}
