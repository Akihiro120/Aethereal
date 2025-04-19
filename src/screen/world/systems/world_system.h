#pragma once
#include <fecs.h>
#include "../../utilities/draw_utilities.h"
#include "../../../components/world_component.h"
#include "noise_system.h"
#include "../../../data/database/database.h"
#include "../../../input/input_manager.h"
#include <memory>

class WorldSystem {
public:
   WorldSystem();
   void generate_world();
   void get_bounds(std::function<void(glm::ivec2 chunk_pos, glm::ivec2 offset_idx)> callback);
   void update();
   void render(const DrawUtils::Box& box);

private:
  	std::shared_ptr<FECS> m_ecs;
	std::shared_ptr<Database> m_database;
	std::shared_ptr<InputManager> m_input_manager;
   uint32_t m_seed = 0;

   Chunk generate_chunk(glm::ivec2 chunk_size, glm::ivec2 chunk_pos);
   void render_chunk(const std::vector<Tile>& tiles, const glm::vec2& offset, glm::ivec2 chunk_size, const DrawUtils::Box& bounds);

   Entity m_world;
	NoiseSystem m_noise_system;
};
