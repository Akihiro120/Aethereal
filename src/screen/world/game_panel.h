#pragma once
#include "../utilities/draw_utilities.h"

class GamePanel {
public:
	GamePanel() = default;

	void render(const DrawUtils::Box& box);
	void update();
};
