#pragma once
#include <fecs.h>
#include <BearLibTerminal.h>
#include <glm/glm.hpp>
#include "../../../services/service_locator.h"
#include "../../../components/camera_component.h"
#include "../../../components/player_component.h"
#include "../../../components/position_component.h"

class CameraSystem {
public:
	CameraSystem() = default;

	void update() {
		// Update the camera position based on the entity's position
		auto ecs = ServiceLocator::get_service<FECS>();
		ecs->query<CameraComponent>([&ecs](Entity entity, auto& camera) {
			
			// track player
			ecs->query<PlayerComponent, PositionComponent>([&camera](Entity e, auto& _, auto& epos) {

				camera.tracking_x = glm::floor(epos.x - (terminal_state(TK_WIDTH) * 0.75f * 0.5f));
				camera.tracking_y = glm::floor(epos.y - (terminal_state(TK_HEIGHT) * 0.75f * 0.5f)) - 3.0f;
			});
		});
	}
};
