#pragma once
#include <fecs.h>
#include "../../utilities/draw_utilities.h"
#include "../../../components/world_component.h"
#include "fast_noise.h"

class WorldSystem {
public:
    WorldSystem();
    void generate_world();
    void get_bounds(std::function<void(glm::ivec2 chunk_pos, glm::ivec2 offset_idx)> callback);
    void update();
    void render(const DrawUtils::Box& box);

private:
    std::shared_ptr<FECS> m_ecs;
    uint32_t m_seed = 0;

    inline int32_t random_pcg();
    inline float random_pcg_float();
    inline int32_t random_pcg_range(int32_t min, int32_t max);
    inline float random_pcg_range_float(float min, float max);

    float m_frequency = 1.0f;
    float m_amplitude = 1.0f;

    Tile generate(float world_x, float world_y);
    Chunk generate_chunk(glm::ivec2 chunk_size, glm::ivec2 chunk_pos);
    void render_chunk(const std::vector<Tile>& tiles, const glm::vec2& offset, glm::ivec2 chunk_size, const DrawUtils::Box& bounds);

    Entity m_world;
    FastNoiseLite m_noise;
};
