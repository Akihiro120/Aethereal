#pragma once
#include <fecs.h>
#include "../../../services/service_locator.h"
#include "../../../components/render_component.h"
#include "../../../components/position_component.h"
#include "../../utilities/draw_utilities.h"

class RenderSystem {
public:
	RenderSystem() = default;

	// render the game world
	void render(const DrawUtils::Box& bounds) {

		auto ecs = ServiceLocator::get_service<FECS>();
		ecs->query<Position, Render>([&](Entity _, Position& pos, Render& render) {

				// TODO:
				// potentially add screen bounds to cull 
				int bound_x = (int)bounds.x + 1;
				int bound_y = (int)bounds.y + 1;
				int bound_width = (int)bounds.width - 1;
				int bound_height = (int)bounds.height - 1;

				if (pos.x >= 0 && pos.x < bound_width &&
					pos.y >= 0 && pos.y < bound_height) {

					// render
					terminal_color(render.color);
					terminal_put(pos.x + bound_x, pos.y + bound_y, render.code);
				}
		});
	}
};
