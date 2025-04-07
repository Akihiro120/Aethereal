#pragma once
#include <fecs.h>
#include "../../utilities/draw_utilities.h"
#include "../../../services/service_locator.h"
#include "../../../components/world_component.h"
#include "../../../components/player_component.h"
#include "../../../components/position_component.h"
#include "fast_noise.h"

class WorldSystem {
public:
	WorldSystem() {
		m_noise = FastNoiseLite();
		m_noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	}

	void generate_world() {

		// generate chunks
		auto ecs = ServiceLocator::get_service<FECS>();
		Entity world = ecs->create_entity();
		ecs->attach<World>(world, {});
	}

	void update() {
		auto ecs = ServiceLocator::get_service<FECS>();
		ecs->query<World>([&](Entity entity, World& world) {

			// calculate distance
			int distance_x_min = 0;
			int distance_x_max = 0;
			int distance_y_min = 0;
			int distance_y_max = 0;
			ecs->query<Player, Position>([
					&distance_x_min,
					&distance_x_max,
					&distance_y_min,
					&distance_y_max
			](Entity entity, Player& _, Position& pos) {
					
				distance_x_min -= pos.x;
				distance_x_max += pos.x;

				distance_y_min -= pos.y;
				distance_y_max += pos.y;
			});

			// render
			for (int y = distance_y_min; y < distance_y_max; y++) {
				for (int x = distance_x_min; x < distance_x_max; x++) {

					int key = x + 10 * y;
					if (world.chunks.find(key) != world.chunks.end()) {

						generate_chunk(world.chunks[key].tiles, glm::vec2(x, y));
					}
				}
			}
		});
	}

	void render(const DrawUtils::Box& box) {

		auto ecs = ServiceLocator::get_service<FECS>();
		ecs->query<World>([&](Entity entity, World& world) {

			// calculate distance
			int distance_x_min = 0;
			int distance_x_max = 0;
			int distance_y_min = 0;
			int distance_y_max = 0;
			ecs->query<Player, Position>([
					&distance_x_min, &distance_x_max,
					&distance_y_min, &distance_y_max
			](Entity entity, Player& _, Position& pos) {
					
				distance_x_min -= pos.x;
				distance_x_max += pos.x;

				distance_y_min -= pos.y;
				distance_y_max += pos.y;
			});

			// render
			for (int y = distance_y_min; y < distance_y_max; y++) {
				for (int x = distance_x_min; x < distance_x_max; x++) {

					int key = x + 10 * y;
					if (world.chunks.find(key) != world.chunks.end()) {

						render_chunk(world.chunks[key].tiles, glm::vec2(x, y));
					}
				}
			}
		});
	}

private:
	void generate_chunk(std::vector<Tile> tiles, const glm::vec2& offset) {

	}

	void render_chunk(std::vector<Tile> tiles, const glm::vec2& offset) {
		int render_distance = 3;
		auto ecs = ServiceLocator::get_service<FECS>();
		

		ecs->query<World>([&](Entity entity, World& world) {

				// create chunk and add
				for (int y = 0; y < world.chunk_size; y++) {
					for (int x = 0; x < world.chunk_size; x++) {

						terminal_put(x + offset.x, y + offset.y, (int)'#');
					}	
				}	
		});
	}

	FastNoiseLite m_noise;
};
