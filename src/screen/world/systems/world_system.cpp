#include "world_system.h"
#include "../../../services/service_locator.h"
#include "../../../components/player_component.h"
#include "../../../components/position_component.h"
#include "../../../components/camera_component.h"
#include "BearLibTerminal.h"
#include <random>

WorldSystem::WorldSystem() {}

void WorldSystem::generate_world() {
    // Initialize ECS and world entity
    m_ecs = ServiceLocator::get_service<FECS>();
    m_world = m_ecs->create_entity();
    m_ecs->attach<WorldComponent>(m_world, {});

    // Generate a random seed for procedural generation
    std::random_device rd;
    m_seed = (static_cast<uint64_t>(rd()) << 32) | rd();

    // Set up noise generator
    m_noise = FastNoiseLite();
    m_noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    m_noise.SetSeed(random_pcg());
}

void WorldSystem::get_bounds(std::function<void(glm::ivec2 chunk_pos, glm::ivec2 offset_idx)> callback) {
    // Retrieve world component and chunk size
    auto world = m_ecs->get<WorldComponent>(m_world);
    glm::ivec2 chunk_size = world->chunk_size;

    // Get the player's position
    glm::vec2 player_pos;
    m_ecs->query<PlayerComponent, PositionComponent>([&](Entity _, auto& player, auto& pos) {
        player_pos = glm::vec2(pos.x, pos.y);
    });

    // Calculate the player's chunk position
    glm::ivec2 player_chunk = {
        (int)glm::floor(player_pos.x / (float)chunk_size.x),
        (int)glm::floor(player_pos.y / (float)chunk_size.y)
    };

    // Define render distance in chunks
    const int rdx = 8;
    const int rdy = glm::floor(rdx * 0.5);

    // Iterate through chunks within the render distance
    for (int dy = -rdy; dy <= rdy; dy++) {
        for (int dx = -rdx; dx <= rdx; dx++) {
            glm::ivec2 offset = {dx, dy};
            glm::ivec2 chunk_pos = player_chunk + offset;
            callback(chunk_pos, offset);
        }
    }
}

void WorldSystem::update() {
    // Retrieve world component and chunk size
    auto world = m_ecs->get<WorldComponent>(m_world);
    glm::ivec2 chunk_size = world->chunk_size;

    // Generate new chunks within bounds if they don't already exist
    get_bounds([&](auto chunk_pos, auto idx) {
        if (world->chunks.find(chunk_pos) == world->chunks.end()) {
            world->chunks[chunk_pos] = generate_chunk(chunk_size, chunk_pos);
        }
    });
}

void WorldSystem::render(const DrawUtils::Box& box) {
    // Retrieve world component and chunk size
    auto world = m_ecs->get<WorldComponent>(m_world);
    glm::ivec2 chunk_size = world->chunk_size;

    // Render visible chunks within the screen bounds
    get_bounds([&](auto chunk_pos, auto idx) {
        auto it = world->chunks.find(chunk_pos);
        if (it != world->chunks.end()) {
            const auto& tiles = it->second.tiles;
            const glm::vec2 offset = chunk_pos * chunk_size;
            render_chunk(tiles, offset, chunk_size, box);
        }
    });
}

inline int32_t WorldSystem::random_pcg() {
    // PCG-based random number generation algorithm
    m_seed = m_seed * 747796405u + 2891336453u;
    uint32_t word = ((m_seed >> ((m_seed >> 28u) + 4u)) ^ m_seed) * 277803737u;
    return (word >> 22u) ^ word;
}

inline float WorldSystem::random_pcg_float() {
    // Generate a random float between 0.0 and 1.0
    union {uint32_t i; float f;} u;
    u.i = (127 << 23) | (random_pcg() >> 9);
    return u.f - 1.0f;
}

inline int32_t WorldSystem::random_pcg_range(int32_t min, int32_t max) {
    // Generate a random integer in the range [min, max]
    uint32_t range = max - min + 1;
    return min + ((uint64_t)random_pcg() * range >> 32);
}

inline float WorldSystem::random_pcg_range_float(float min, float max) {
    // Generate a random float in the range [min, max]
    return min + (max - min) * random_pcg_float();
    
}

// world generation type shit


Tile WorldSystem::generate(float world_x, float world_y) {
    // Generate noise-based height for the tile

    // fbm
    float amp = m_amplitude;
    float freq = m_frequency;
    float height = 0.0f;
    for (int i = 0; i < 4; i++) {

        height += m_noise.GetNoise(world_x * freq / 2.0f, world_y * freq) * amp;

        // fbm
        amp *= 0.5f;
        freq *= 2.0f;
    }

    // normalize
    height = (height + 1.0f) * 0.5f;

    // base tile data
    RenderComponent r;
    bool c = false;

    // Assign tile properties based on the height value
    if (height < 0.05f) {
        r = {
            .code = 0x2248,
            .color = color_from_name("blue"),
            .bg_color = color_from_name("black")
        };
    } else if (height <= 0.7f) {
        float foliage_bias = random_pcg_range_float(0.0f, 1.0f);
        if (foliage_bias < 0.05f) {
            r = {
                .code = 0x2663,
                .color = color_from_name("dark green"),
                .bg_color = color_from_name("black")
            };
        } else if (foliage_bias <= 0.15f) {
            r = {
                .code = (int)',',
                .color = color_from_name("green"),
                .bg_color = color_from_name("black")
            };
        }
    } else if (height <= 0.8f) {
        r = {
            .code = 0x25B4,
            .color = color_from_name("grey"),
            .bg_color = color_from_name("black")
        };
    } else if (height <= 1.0f) {
        r = {
            .code = 0x25B2,
            .color = color_from_name("white"),
            .bg_color = color_from_name("black")
        };
    }
    
    return {
        .render = r,
        .collidable = c
    };
}

Chunk WorldSystem::generate_chunk(glm::ivec2 chunk_size, glm::ivec2 chunk_pos) {
    // Initialize a new chunk and allocate space for tiles
    Chunk chunk = {};
    chunk.tiles.resize(chunk_size.x * chunk_size.y);

    // Generate tiles for the chunk
    for (int y = 0; y < chunk_size.y; y++) {
        for (int x = 0; x < chunk_size.x; x++) {
            const int world_x = x + chunk_pos.x * chunk_size.x;
            const int world_y = y + chunk_pos.y * chunk_size.y;
            chunk.tiles[x + chunk_size.x * y] = generate(world_x, world_y);
        }
    }

    return chunk;
}

void WorldSystem::render_chunk(const std::vector<Tile>& tiles, const glm::vec2& offset, glm::ivec2 chunk_size, const DrawUtils::Box& bounds) {
    // Retrieve camera position
    int cam_x, cam_y;
    m_ecs->query<CameraComponent>([&](Entity _, auto& camera) {
        cam_x = camera.tracking_x;
        cam_y = camera.tracking_y;
    });

    // Define screen bounds
    const int screen_x = (float)bounds.x + 1;
    const int screen_y = (float)bounds.y + 1;
    const int screen_width = (float)bounds.width;
    const int screen_height = (float)bounds.height;

    // Render each tile in the chunk if visible on screen
    for (int y = 0; y < chunk_size.y; y++) {
        for (int x = 0; x < chunk_size.x; x++) {
            const int pos_x = x + offset.x - cam_x;
            const int pos_y = y + offset.y - cam_y;

            if (pos_x < screen_x || pos_x >= screen_width || pos_y < screen_y || pos_y >= screen_height) {
                continue;
            }

            int index = x + chunk_size.x * y;
            if (tiles[index].render.code == 0x00) {
                continue;
            }
            terminal_bkcolor(tiles[index].render.bg_color);
            terminal_color(tiles[index].render.color);
            terminal_put(pos_x, pos_y, tiles[index].render.code);
        }
    }
}
