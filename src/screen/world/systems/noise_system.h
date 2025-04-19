#pragma once
#include <random>
#include "../../../components/world_component.h"
#include "fast_noise.h"
#include "../../../data/database/database.h"
#include "../../../services/service_locator.h"

struct NoiseLayers {
	float amplitude = 1.0f;
	float frequency = 0.1f;

	int octave = 1;
	float persistence = 0.5f;
	float lacunarity = 2.0f;

	FastNoiseLite noise;

	// generation stuff
	
};

class NoiseSystem {
public:
	NoiseSystem() {
		// get the databaso
		m_db = ServiceLocator::get_service<Database>();
		
		// generate a random seed
		std::random_device rd;
		m_seed = rd();

		// begin parsing
		parse_noise();
	}

	Tile generate(float x, float z) {
		// manipulate the shape
		float world_x = x * 1.0f;
		float world_z = z * 2.0f;

		return generate_tile(world_x, world_z);
	}

private:
	color_t color_from_hex(const std::string& hex) {
		// convert hex to color
		int r = std::stoi(hex.substr(1, 2), nullptr, 16);
		int g = std::stoi(hex.substr(3, 2), nullptr, 16);
		int b = std::stoi(hex.substr(5, 2), nullptr, 16);
		return color_from_argb(255, r, g, b);
		
	}

	void parse_noise() {

	}
	
   Tile generate_structures(float x, float z) {
      Tile tile = {};
      return tile;
   }

	Tile generate_tile(float x, float z) {
		// generate the tile
		Tile tile = {};

		// // generate the noise
		// float frequency = 0.1f;
		// float amplitude = 1.0f;
		// float elevation = 0.0f;//compute_noise(x, z);
		// for (int i = 0; i < 8; i++) {
		// 	float noise = compute_noise(x * frequency, z * frequency) * amplitude;
		// 	elevation += noise;
		//
		// 	frequency *= 4.0f;
		// 	amplitude *= 0.5f;	
		// }
		//       elevation = elevation * 0.5f + 0.5f; // normalize to [0, 1]
		//
		// // sample
		// // TODO: add blending and interpolation between elevation levels
		// if (elevation < 0.325f) {
		// 	// water
		//           tile = generate_water_tiles(x, z);
		//       } else if (elevation < 0.35f) {
		// 	tile.render.code = '~';
		// 	tile.render.color = color_from_name("white");
		// } else if (elevation < 0.4f) {
		// 	// sand
		// 	tile.render.code = '+';
		// 	tile.render.color = color_from_name("yellow");
		//           tile.tags = {Tag::HARVESTABLE, Tag::PERSISTENT};
		//           tile.yield = 0;
		//           tile.tile_obj_id = "sand";
		// } else if (elevation < 0.675f) {
		// 	// grass
		// 	tile = generate_grassland_tiles(x, z);
		// } else {
		//           tile = generate_mountain_tiles(x, z);
		//       }

		return tile;
	}

	//    Tile generate_mountain_tiles(float x, float z) {
	//        Tile tile = {};
	//
	//        float mountain_height = 0.0f;
	//        float frequency = 0.1f;
	//        float amplitude = 1.0f;
	//        for (int i = 0; i < 8; i++) {
	//            float noise = m_mountain_noise.GetNoise(x * frequency, z * frequency) * amplitude;
	//            mountain_height += noise;
	//
	//            frequency *= 8.0f;
	//            amplitude *= 0.5f;	
	//        }
	//        mountain_height = glm::pow(1.0f * glm::abs(mountain_height), 2);
	//        mountain_height = mountain_height * 0.5f + 0.5f; // normalize to [0, 1]
	//
	//        if (mountain_height < 0.6f) {
	//            tile.render.code = 0xf47e;
	//            tile.tags = {Tag::HARVESTABLE};
	//            tile.yield = random_pcg_range(2, 20);
	//
	//            float ore = random_pcg_range_float(0.0f, 100.0f);
	//            if (ore < 15.0f) {
	//                tile.tile_obj_id = "platinum";
	//            } else {
	//                tile.tile_obj_id = "stone";
	//            }
	//        } else if (mountain_height < 0.7f) {
	//            tile.render.code = 0xeb71;
	//            tile.collidable = true;
	//        } else if (mountain_height < 0.812f) {
	//            tile.render.code = 0x25B2;
	//            tile.collidable = true;
	//        } else {
	//
	//        }
	//
	//        glm::ivec3 mountain_color_light = glm::ivec3(255, 255, 255);
	//        glm::ivec3 mountain_color_dark = glm::ivec3(125, 125, 125);
	//        float mountain_color_curve = mountain_height * 2.0f - 1.0f;
	//        tile.render.color = color_from_argb(255, 
	//            glm::mix(mountain_color_dark.r, mountain_color_light.r, mountain_color_curve),
	//            glm::mix(mountain_color_dark.g, mountain_color_light.g, mountain_color_curve),
	//            glm::mix(mountain_color_dark.b, mountain_color_light.b, mountain_color_curve)
	//        ); 
	//
	//        return tile;
	//    }
	//
	//    Tile generate_water_tiles(float x, float z) {
	//        Tile tile = {};
	//
	//        glm::ivec3 water_color_light = glm::ivec3(31, 139, 255);
	//        glm::ivec3 water_color_dark = glm::ivec3(0, 204, 240);
	//
	//        float height = 0.0f;//
	//        float frequency = 0.1f;
	//        float amplitude = 1.0f;
	//        for (int i = 0; i < 8; i++) {
	//            float noise = m_water_noise.GetNoise(x * frequency, z * frequency) * amplitude;
	//            height += noise;
	//
	//            frequency *= 6.0f;
	//            amplitude *= 0.5f;	
	//        }
	//        height = height * 0.5f + 0.5f; // normalize to [0, 1]
	//
	//        if (height < 0.5f) {
	//            tile.render.code = '~';
	//        } else {
	//            tile.render.code = 0x2248;
	//        }
	//        tile.render.color = color_from_argb(255, 
	//            glm::mix(water_color_dark.r, water_color_light.r, height),
	//            glm::mix(water_color_dark.g, water_color_light.g, height),
	//            glm::mix(water_color_dark.b, water_color_light.b, height)
	//        );
	//        tile.tags = {Tag::HARVESTABLE, Tag::PERSISTENT};
	//        tile.yield = 0;
	//        tile.tile_obj_id = "water";
	//
	//        return tile;
	//    }
	//
	// Tile generate_grassland_tiles(float x, float z) {
	//
	// 	Tile tile = {};
	//
	// 	float grass_chance = random_pcg_range_float(0.0f, 100.0f);
	// 	if (grass_chance < 7.0f) {
	//
	// 		int grass_variant = random_pcg_range(0, 3);
	// 		tile.render.color = color_from_name("green");
	// 		if (grass_variant == 0) {
	// 			tile.render.code = ',';
	// 		} else if (grass_variant == 1) {
	// 			tile.render.code = '"';
	// 		} else if (grass_variant == 2) {
	// 			tile.render.code = '\'';
	// 		} else if (grass_variant == 3) {
	// 			tile.render.code = '.';
	// 		}
	//
	// 	} else if (grass_chance < 8.0f) {
	//            tile.render.code = 0x23AF;
	//            tile.render.color = color_from_argb(255, 66, 39, 0);
	//            tile.tile_obj_id = "stick";
	//            tile.tags = {Tag::HARVESTABLE};
	//        }
	//
	// 	return tile;
	// }
	//
	// float compute_noise(float x, float z) {
	// 	// generate the noise
	// 	float noise = m_noise.GetNoise(x, z);
	// 	return noise;
	// }

	// random number generators
	inline int32_t random_pcg() {
		 // PCG-based random number generation algorithm
		 m_seed = m_seed * 747796405u + 2891336453u;
		 uint32_t word = ((m_seed >> ((m_seed >> 28u) + 4u)) ^ m_seed) * 277803737u;
		 return (word >> 22u) ^ word;
	}

	inline float random_pcg_float() {
		 // Generate a random float between 0.0 and 1.0
		 union {uint32_t i; float f;} u;
		 u.i = (random_pcg() >> 9) | 0x3F800000; 
		 return u.f - 1.0f;
	}

	inline int32_t random_pcg_range(int32_t min, int32_t max) {
		 // Generate a random integer in the range [min, max]
		 uint32_t range = max - min + 1;
		 return min + ((uint64_t)random_pcg() % range);
	}

	inline float random_pcg_range_float(float min, float max) {
		 // Generate a random float in the range [min, max]
		 return min + (max - min) * random_pcg_float();
		 
	}

	// members
	int32_t m_seed = 0;

	// noise
	std::unordered_map<std::string, Noise> m_noise_map;

	// systemss
	std::shared_ptr<Database> m_db;
};
