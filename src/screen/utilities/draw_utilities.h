#pragma once
#include <BearLibTerminal.h>
#include "../../data/enums/unicodes.h"

namespace DrawUtils {

	struct Box {
		int x, y, width, height;

		// Constructor
		Box(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}
	};

	// draw a rectangle
	inline void draw_box_light(const Box& box) {
		// horizontal lines
		for (int x = 0; x < box.width; x++) {
			terminal_put(x + box.x, 0 + box.y, (int)Unicode::BoxLight::HORIZONTAL);
			terminal_put(x + box.y, box.height + box.y, (int)Unicode::BoxLight::HORIZONTAL);
		}

		// vertical lines
		for (int y = 0; y < box.height; y++) {
			terminal_put(0 + box.x, y + box.y, (int)Unicode::BoxLight::VERTICAL);
			terminal_put(box.width + box.x, y + box.y, (int)Unicode::BoxLight::VERTICAL);
		}

		// corners
		terminal_put(0, 0, (int)Unicode::BoxLight::TOP_LEFT);
		terminal_put(box.width, 0, (int)Unicode::BoxLight::TOP_RIGHT);
		terminal_put(0, box.height, (int)Unicode::BoxLight::BOTTOM_LEFT);
		terminal_put(box.width, box.height, (int)Unicode::BoxLight::BOTTOM_RIGHT);
	}	
	
	// draw a rectangle
	inline void draw_box_heavy(const Box& box) {
		// horizontal lines
		for (int x = 0; x < box.width; x++) {
			terminal_put(x + box.x, 0 + box.y, (int)Unicode::BoxHeavy::HORIZONTAL);
			terminal_put(x + box.y, box.height + box.y, (int)Unicode::BoxHeavy::HORIZONTAL);
		}

		// vertical lines
		for (int y = 0; y < box.height; y++) {
			terminal_put(0 + box.x, y + box.y, (int)Unicode::BoxHeavy::VERTICAL);
			terminal_put(box.width + box.x, y + box.y, (int)Unicode::BoxHeavy::VERTICAL);
		}

		// corners
		terminal_put(0, 0, (int)Unicode::BoxHeavy::TOP_LEFT);
		terminal_put(box.width, 0, (int)Unicode::BoxHeavy::TOP_RIGHT);
		terminal_put(0, box.height, (int)Unicode::BoxHeavy::BOTTOM_LEFT);
		terminal_put(box.width, box.height, (int)Unicode::BoxHeavy::BOTTOM_RIGHT);
	}
}
