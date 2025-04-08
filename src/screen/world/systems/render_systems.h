#pragma once
#include <fecs.h>
#include "../../../services/service_locator.h"
#include "../../../components/render_component.h"
#include "../../../components/position_component.h"
#include "../../../components/camera_component.h"
#include "../../utilities/draw_utilities.h"
#include "BearLibTerminal.h"

class RenderSystem {
public:
	RenderSystem() = default;

	// render the game world
	void render(const DrawUtils::Box& bounds) {

		auto ecs = ServiceLocator::get_service<FECS>();
		int cam_x, cam_y;
		ecs->query<Camera>([&](Entity _, Camera& camera) {
			cam_x = camera.tracking_x;
			cam_y = camera.tracking_y;
		});

		const int screen_x = (float)bounds.x+1;
		const int screen_y = (float)bounds.y+1;
		const int screen_width = (float)bounds.width;
		const int screen_height = (float)bounds.height;

		ecs->query<Position, Render>([&](Entity _, Position& pos, Render& render) {
				int screen_pos_x = pos.x - cam_x;
				int screen_pos_y = pos.y - cam_y;

				// cull
				if (screen_pos_x < screen_x || screen_pos_x >= screen_width ||
					screen_pos_y < screen_y || screen_pos_y >= screen_height) {
					return;
				}

				// render
				terminal_bkcolor(render.bg_color);
				terminal_color(render.color);
				terminal_put(screen_x + screen_pos_x, screen_y + screen_pos_y, render.code);
		});
	}
};
