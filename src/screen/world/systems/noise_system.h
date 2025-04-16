#pragma once
#include <random>
#include "../../../components/world_component.h"
#include "fast_noise.h"

class NoiseSystem {
public:
	NoiseSystem() {
		// generate a random seed
		std::random_device rd;
		m_seed = rd();

		// setup noise
		m_noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
		m_noise.SetSeed(m_seed);
	}

	Tile generate(float x, float z) {
		// manipulate the shape
		float world_x = x * 1.0f;
		float world_z = z * 2.0f;

		return generate_tile(world_x, world_z);
	}

private:
	Tile generate_tile(float x, float z) {
		// generate the tile
		Tile tile = {};

		// generate the noise
		float frequency = 0.1f;
		float amplitude = 1.0f;
		float elevation = 0.0f;//compute_noise(x, z);
		for (int i = 0; i < 8; i++) {
			float noise = compute_noise(x * frequency, z * frequency) * amplitude;
			elevation += noise;

			frequency *= 4.0f;
			amplitude *= 0.5f;	
		}

		// sample
		// TODO: add blending and interpolation between elevation levels
		if (elevation < 0.01) {
			// water
			tile.render.code = '~';
			tile.render.color = color_from_name("blue");
		} else if (elevation < 0.1) {
			// sand
			tile.render.code = '-';
			tile.render.color = color_from_name("yellow");
		} else if (elevation < 0.7) {
			// grass
			tile = generate_grassland_tiles(x, z);
		} else if (elevation < 0.8) {
			// mountains
			tile.render.code = 0x25B4;
			tile.render.color = color_from_name("grey");
			tile.collidable = true;

			// TODO: use another layer of noise to generate mountain types
		} else {
			// snow
			tile.render.code = 0x25B2;
			tile.render.color = color_from_name("white");
		}

		return tile;
	}

	Tile generate_grassland_tiles(float x, float z) {

		// generate foliage

		// trees
		//	rocks
		//	flowers
		//	- yellow
		//	- red
		//	- grass
		//	add patches of flowers, grass variants

		Tile tile = {};
		
		float grass_chance = random_pcg_range_float(0.0f, 100.0f);
		if (grass_chance < 10.0f) {
			
			int grass_variant = random_pcg_range(0, 3);
			tile.render.color = color_from_name("green");
			if (grass_variant == 0) {
				tile.render.code = ',';
			} else if (grass_variant == 1) {
				tile.render.code = '"';
			} else if (grass_variant == 2) {
				tile.render.code = '\'';
			} else if (grass_variant == 3) {
				tile.render.code = '.';
			}
		}
		
		return tile;
	}

	float compute_noise(float x, float z) {
		// generate the noise
		float noise = m_noise.GetNoise(x, z);
		return noise;
	}

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

	// noise functions
	FastNoiseLite m_noise;
};
