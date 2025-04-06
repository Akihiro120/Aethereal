#pragma once
#include "../utilities/draw_utilities.h"

class MessagePanel {
public:
	MessagePanel() = default;

	void render(const DrawUtils::Box& box);
	void update();
};
