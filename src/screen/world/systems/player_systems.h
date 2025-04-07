#pragma once
#include <BearLibTerminal.h>
#include <fecs.h>
#include "../../../services/service_locator.h"
#include "../../../components/velocity_component.h"
#include "../../../components/player_component.h"

class PlayerSystem {
public:
	PlayerSystem() = default;

	// control player movement
	void movement(int key) {
		auto ecs = ServiceLocator::get_service<FECS>();
		ecs->query<Player, Velocity>([&](Entity _1, auto& _2, Velocity& vel) {
			if (key == TK_H || key == TK_LEFT) {
				vel.x -= 1.0f;
			}	
			if (key == TK_J || key == TK_DOWN) {
				vel.y += 1.0f;
			}	
			if (key == TK_K || key == TK_UP) {
				vel.y -= 1.0f;
			}	
			if (key == TK_L || key == TK_RIGHT) {
				vel.x += 1.0f;
			}	
		});
	}
};
