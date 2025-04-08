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

	void get_bounds(std::function<void(glm::ivec2 chunk_pos, glm::ivec2 offset_idx)> callback) {
		// generate world
		auto ecs = ServiceLocator::get_service<FECS>();
		auto world = ecs->get<World>(m_world);
		glm::ivec2 chunk_size = world->chunk_size;

		glm::vec2 player_pos;
		ecs->query<Player, Position>([&](Entity _, Player&, Position& pos) {
			player_pos = glm::vec2(pos.x, pos.y);
		});

		glm::ivec2 player_chunk = {
			(int)glm::floor(player_pos.x / (float)chunk_size.x),
			(int)glm::floor(player_pos.y / (float)chunk_size.y)
		};

		// render distance
		const int rdx = 8;
		const int rdy = glm::floor(rdx * 0.5);

		// get bounds
		for (int dy = -rdy; dy <= rdy; dy++) {
			for (int dx = -rdx; dx <= rdx; dx++) {
				glm::ivec2 offset = {dx, dy};
				glm::ivec2 chunk_pos = player_chunk + offset; 

				callback(chunk_pos, offset);
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
				world->chunks[chunk_pos] = generate_chunk(chunk_size, chunk_pos);
			}	
		});
	}

	void render(const DrawUtils::Box& box) {

		auto ecs = ServiceLocator::get_service<FECS>();
		auto world = ecs->get<World>(m_world);
		glm::ivec2 chunk_size = world->chunk_size;

		get_bounds([&](auto chunk_pos, auto idx) {

			auto it = world->chunks.find(chunk_pos);
			if (it != world->chunks.end()) {
				const auto& tiles = world->chunks[chunk_pos].tiles;
				const glm::vec2 offset = chunk_pos * chunk_size;
				render_chunk(tiles, offset, chunk_size, box);
			}	
		});
	}

private:
	Chunk generate_chunk(glm::ivec2 chunk_size, glm::ivec2 chunk_pos) {
		Chunk chunk = {};
		chunk.tiles.resize(chunk_size.x * chunk_size.y);

		for (int y = 0; y < chunk_size.y; y++) {
			for (int x = 0; x < chunk_size.x; x++) {
				const int world_x = x + chunk_pos.x * chunk_size.x;
				const int world_y = y + chunk_pos.y * chunk_size.y;

				const color_t color = color_from_argb(
						255, 
						(world_x * 8) % 255,
						(world_y * 8) % 255,
						(world_x + world_y) % 255
				);

				float height = m_noise.GetNoise((float)world_x, (float)world_y * 2.0f);
				
				if (height < 0.0f) {
					int height_greyscale = (int)(height * 255.0f);
					chunk.tiles[x + chunk_size.x * y] = Tile {
						.render = Render {
							.code = (int)'#', 
							.color = color_from_argb(255, 
								(world_x * 8) % 255,
								(world_y * 8) % 255,
								height_greyscale	
							),
							.bg_color = color_from_argb(255, 
								height_greyscale, height_greyscale, height_greyscale),
						},
						.collidable = true,
					};
				}
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
				terminal_bkcolor(tiles[index].render.bg_color);
				terminal_color(tiles[index].render.color);
				terminal_put(pos_x, pos_y, tiles[index].render.code);
			}
		}
	}

	Entity m_world;
	FastNoiseLite m_noise;
};
