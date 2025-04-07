#pragma once
#include "../../data/enums/unicodes.h"

namespace DrawUtils {

	struct Box {
		float x, y, width, height;

		// Constructor
		Box(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}
		Box(int x, int y, int width, int height) : x((float)x), y((float)y), width((float)width), height((float)height) {}
		Box() : x(0), y(0), width(0), height(0) {}
	};

	// draw a rectangle
	inline void draw_box_light(const Box& box) {
		// horizontal lines
		for (int x = 0; x < box.width; x++) {
			terminal_put(x + box.x, 0 + box.y, (int)Unicode::BoxLight::HORIZONTAL);
			terminal_put(x + box.x, box.height + box.y, (int)Unicode::BoxLight::HORIZONTAL);
		}

		// vertical lines
		for (int y = 0; y < box.height; y++) {
			terminal_put(0 + box.x, y + box.y, (int)Unicode::BoxLight::VERTICAL);
			terminal_put(box.width + box.x, y + box.y, (int)Unicode::BoxLight::VERTICAL);
		}

		// corners
		terminal_put(box.x, box.y, (int)Unicode::BoxLight::TOP_LEFT);
		terminal_put(box.width + box.x, box.y, (int)Unicode::BoxLight::TOP_RIGHT);
		terminal_put(box.x, box.height + box.y, (int)Unicode::BoxLight::BOTTOM_LEFT);
		terminal_put(box.width + box.x, box.height + box.y, (int)Unicode::BoxLight::BOTTOM_RIGHT);
	}	
	
	// draw a rectangle
	inline void draw_box_heavy(const Box& box) {
		// horizontal lines
		for (int x = 0; x < box.width; x++) {
			terminal_put(x + box.x, 0 + box.y, (int)Unicode::BoxHeavy::HORIZONTAL);
			terminal_put(x + box.x, box.height + box.y, (int)Unicode::BoxHeavy::HORIZONTAL);
		}

		// vertical lines
		for (int y = 0; y < box.height; y++) {
			terminal_put(0 + box.x, y + box.y, (int)Unicode::BoxHeavy::VERTICAL);
			terminal_put(box.width + box.x, y + box.y, (int)Unicode::BoxHeavy::VERTICAL);
		}

		// corners
		terminal_put(box.x, box.y, (int)Unicode::BoxHeavy::TOP_LEFT);
		terminal_put(box.width + box.x, box.y, (int)Unicode::BoxHeavy::TOP_RIGHT);
		terminal_put(box.x, box.height + box.y, (int)Unicode::BoxHeavy::BOTTOM_LEFT);
		terminal_put(box.width + box.x, box.height + box.y, (int)Unicode::BoxHeavy::BOTTOM_RIGHT);
	}
}
