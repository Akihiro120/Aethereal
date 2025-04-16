#pragma once
#include <BearLibTerminal.h>
#include <cstdint>
#include <fecs.h>
#include "../../../services/service_locator.h"
#include "../../../components/position_component.h"
#include "../../../components/velocity_component.h"
#include "../../../components/world_component.h"
#include "../../../components/collider_component.h"
#include "utility.h"

class PhysicsSystem {
public:
	PhysicsSystem() {
		m_ecs = ServiceLocator::get_service<FECS>();
	}

	// resolve physics
	void resolve_velocities() {
		
		m_ecs->query<PositionComponent, VelocityComponent>([&](Entity _, auto& pos, auto& vel) {
			pos.x += vel.x;
			pos.y += vel.y;

			// reset velocity
			vel.x = 0.0f;
			vel.y = 0.0f;
		});
	}

	void calculate_spatial_map() {
		// get all the dynamic entities, dynamic entities have a velocity
		// static entities do not, but it also must have a collider
		m_ecs->query<ColliderComponent, VelocityComponent>([](Entity id, auto& collider, auto& vel){

		});
	}

	void resolve_collisions() {
		// chunk bounds
		const int rdx = m_collision_range;
		const int rdy = glm::floor(rdx * 0.5);

		// terrain collisions
		// all terrain units are always static
		m_ecs->query<WorldComponent>([&](Entity _, WorldComponent& world) {
			// resolve terrain collisions for all entities
			// get its location, query its position relative to chunk
			// get the 8 tiles, next to it, if its a collidable tile, then go next
			// take care of edge cases like the adjacent tiles are in different chunk bounds
			m_ecs->query<ColliderComponent>([&](Entity id, auto& collider) {

				// get the position, and velocity
				auto pos_ref = m_ecs->get<PositionComponent>(id);
				auto vel_ref = m_ecs->get<VelocityComponent>(id);

				// calculate the next position based on velocity
				glm::ivec2 next_pos = glm::ivec2(
					pos_ref->x + vel_ref->x,
					pos_ref->y + vel_ref->y
				);

                GameUtils::get_tile_world(world, next_pos, [&](Tile* tile) {
                    if (tile->collidable) {
                        vel_ref->x = 0;
						vel_ref->y = 0;
                    }
                });
			});
		});

		// using a spatial map, dynamic collisions
	}

private:
	int32_t m_collision_range = 2;

	// shared pointer to the ecs
	std::shared_ptr<FECS> m_ecs;
};
