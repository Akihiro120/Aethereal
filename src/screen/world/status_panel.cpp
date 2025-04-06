#include "status_panel.h"


void StatusPanel::render(const DrawUtils::Box& box) {
	// status panel
	terminal_color("white");

	// status
	DrawUtils::draw_box_heavy(box);
	terminal_color("white");
	terminal_print(box.x + 1, 1, "Player");

	// stats
	terminal_print(box.x + 1, 2, "Title");
	terminal_print(box.x + 1, 4, "Health");
	terminal_print(box.x + 1, 5, "Mana");
	terminal_print(box.x + 1, 6, "Stamina");

	// values
	terminal_print(box.x + 10, 2, "Talentless");
	terminal_color("green");
	terminal_print(box.x + 10, 4, "100");
	terminal_print(box.x + 10, 5, "100");
	terminal_print(box.x + 10, 6, "100");
}

void StatusPanel::update() {
	// update status panel
}
