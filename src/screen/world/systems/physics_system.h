#pragma once
#include <BearLibTerminal.h>
#include <fecs.h>
#include "../../../services/service_locator.h"
#include "../../../components/position_component.h"
#include "../../../components/velocity_component.h"

class PhysicsSystem {
public:
	PhysicsSystem() = default;

	// resolve physics
	void resolve_velocities() {
		
		auto ecs = ServiceLocator::get_service<FECS>();
		ecs->query<PositionComponent, VelocityComponent>([&](Entity _, auto& pos, auto& vel) {
			pos.x += vel.x;
			pos.y += vel.y;

			// reset velocity
			vel.x = 0.0f;
			vel.y = 0.0f;
		});
	}
};
