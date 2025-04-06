#include "game_panel.h"

#include "../utilities/draw_utilities.h"

void GamePanel::render(const DrawUtils::Box& box) {
	// game panel
	terminal_color("white");
	DrawUtils::draw_box_heavy(box);
}

void GamePanel::update() {
	// update game panel
}
