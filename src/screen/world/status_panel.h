#pragma once
#include "../utilities/draw_utilities.h"
#include <fecs.h>

class StatusPanel {
public:
	StatusPanel() = default;

	void render(const DrawUtils::Box& box);
	void update();

private:
	Entity m_player_reference = 0;
};
