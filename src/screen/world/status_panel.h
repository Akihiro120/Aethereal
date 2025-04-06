#pragma once
#include "../utilities/draw_utilities.h"

class StatusPanel {
public:
	StatusPanel() = default;

	void render(const DrawUtils::Box& box);
	void update();
};
