#pragma once
#include <fecs.h>
#include "../../utilities/draw_utilities.h"
#include "../../../services/service_locator.h"
#include "../../../components/world_component.h"
#include "../../../components/player_component.h"
#include "../../../components/position_component.h"
#include "../../../components/camera_component.h"
#include "BearLibTerminal.h"
#include "fast_noise.h"

class WorldSystem {
public:
	WorldSystem() {
	}

	void generate_world() {

		// generate chunks
		auto ecs = ServiceLocator::get_service<FECS>();
		m_world = ecs->create_entity();
		ecs->attach<World>(m_world, {});

		m_noise = FastNoiseLite();
		m_noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
		m_noise.SetSeed(ecs->get<World>(m_world)->seed);

	}

	void get_bounds(std::function<void(glm::ivec2 chunk_pos, glm::ivec2 idx)> callback, glm::ivec2 chunk_size) {
		// generate world
		auto ecs = ServiceLocator::get_service<FECS>();

		float p_pos_x, p_pos_y;
		ecs->query<Player, Position>([
				&p_pos_x, &p_pos_y
		](Entity _, Player&, Position& pos) {
			p_pos_x = pos.x;
			p_pos_y = pos.y;
		});

		glm::vec2 player_chunk = {
			(float)floor(p_pos_x / chunk_size.x),
			(float)floor(p_pos_y / chunk_size.y)
		};

		// render distance
		const int rdx = 8;
		const int rdy = glm::floor(rdx * 0.5);
		
		// calculate bounds
		const int start_x = player_chunk.x - rdx;
		const int start_y = player_chunk.y - rdy;
		const int end_x = player_chunk.x + rdx;
		const int end_y = player_chunk.y + rdy;

		// get bounds
		for (int dy = start_y; dy <= end_y; dy++) {
			for (int dx = start_x; dx <= end_x; dx++) {
				glm::ivec2 chunk_pos = player_chunk + glm::vec2{dx, dy};

				callback(chunk_pos, glm::ivec2{dx, dy});
			}
		}
	}

	void update() {

		// generate world
		auto ecs = ServiceLocator::get_service<FECS>();
		auto world = ecs->get<World>(m_world);
		glm::ivec2 chunk_size = world->chunk_size;

		get_bounds([&](auto chunk_pos, auto idx) {

			if (world->chunks.find(chunk_pos) == world->chunks.end()) {
				world->chunks[chunk_pos] = generate_chunk(world->chunk_size);
			}	
		}, chunk_size);
	}

	void render(const DrawUtils::Box& box) {

		auto ecs = ServiceLocator::get_service<FECS>();
		auto world = ecs->get<World>(m_world);
		glm::ivec2 chunk_size = world->chunk_size;

		get_bounds([&](auto chunk_pos, auto idx) {

			if (world->chunks.find(chunk_pos) != world->chunks.end()) {
				auto tiles = world->chunks[chunk_pos].tiles;
				render_chunk(tiles, {idx.x * chunk_size.x, idx.y * chunk_size.y}, chunk_size, box);
			}	
		}, chunk_size);
	}

private:
	Chunk generate_chunk(glm::ivec2 chunk_size) {
		Chunk chunk = {};
		chunk.tiles.resize(chunk_size.x * chunk_size.y);

		for (int y = 0; y < chunk_size.y; y++) {
			for (int x = 0; x < chunk_size.x; x++) {
				
				chunk.tiles[x + chunk_size.x * y] = Tile {
					.render = Render {
						.code = (int)'#', 
						.color = color_from_argb(255, (x * 8) % 255, (y * 8) % 255, (x * 40 + y * 20) % 255),
					},
					.collidable = true,
				};
			}
		}

		return chunk;
	}

	void render_chunk(const std::vector<Tile>& tiles, const glm::vec2& offset, glm::ivec2 chunk_size, const DrawUtils::Box& bounds) {
		int cam_x, cam_y;
		auto ecs = ServiceLocator::get_service<FECS>();
		ecs->query<Camera>([&](Entity _, Camera& camera) {
			cam_x = camera.tracking_x;
			cam_y = camera.tracking_y;
		});

		const int screen_x = (float)bounds.x+1;
		const int screen_y = (float)bounds.y+1;
		const int screen_width = (float)bounds.width;
		const int screen_height = (float)bounds.height;

		for (int y = 0; y < chunk_size.y; y++) {
			for (int x = 0; x < chunk_size.x; x++) {
				const int pos_x = x + offset.x - cam_x;
				const int pos_y = y + offset.y - cam_y;

				if (pos_x < screen_x ||pos_x >= screen_width ||
					pos_y < screen_y || pos_y >= screen_height) {
					continue;
				}

				int index = x + chunk_size.x * y;
				terminal_color(tiles[index].render.color);
				terminal_put(pos_x, pos_y, tiles[index].render.code);
			}
		}
	}

	Entity m_world;
	FastNoiseLite m_noise;
};
