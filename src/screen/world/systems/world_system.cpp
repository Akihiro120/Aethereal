#include "world_system.h"
#include "../../../services/service_locator.h"
#include "../../../components/player_component.h"
#include "../../../components/position_component.h"
#include "../../../components/camera_component.h"
#include "BearLibTerminal.h"

WorldSystem::WorldSystem() {}

void WorldSystem::generate_world() {
  // Initialize ECS and world entity
  	m_ecs = ServiceLocator::get_service<FECS>();
	m_database = ServiceLocator::get_service<Database>();
	m_input_manager = ServiceLocator::get_service<InputManager>();

	// create world
  	m_world = m_ecs->create_entity();
  	m_ecs->attach<WorldComponent>(m_world, {});
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

	// hot reload
	m_input_manager->process_input([this](int key) {
		if (key == TK_R && terminal_state(TK_CONTROL)) {
			m_database->hot_reload("world");
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



Chunk WorldSystem::generate_chunk(glm::ivec2 chunk_size, glm::ivec2 chunk_pos) {
   // Initialize a new chunk and allocate space for tiles
   Chunk chunk = {};
   chunk.tiles.resize(chunk_size.x * chunk_size.y);

   // Generate tiles for the chunk
   for (int y = 0; y < chunk_size.y; y++) {
       for (int x = 0; x < chunk_size.x; x++) {
           const int world_x = x + chunk_pos.x * chunk_size.x;
           const int world_y = y + chunk_pos.y * chunk_size.y;
           chunk.tiles[x + chunk_size.x * y] = m_noise_system.generate(world_x, world_y);
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
           const int pos_x = x + offset.x - cam_x + 1;
           const int pos_y = y + offset.y - cam_y + 1;

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
