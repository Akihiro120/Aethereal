#include "message_panel.h"

#include "../utilities/draw_utilities.h"

void MessagePanel::render(const DrawUtils::Box& box) {
	// message panel
	terminal_color("white");
	DrawUtils::draw_box_heavy(box);
}

void MessagePanel::update() {
	// update message panel
}
