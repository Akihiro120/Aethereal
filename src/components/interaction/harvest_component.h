#pragma once
#include <glm/glm.hpp>

struct HarvestComponent {
    bool is_harvesting = false;
    glm::vec2 selected_tile_pos;
};
