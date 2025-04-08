#include "talent.h"
#include <BearLibTerminal.h>
#include "../utilities/draw_utilities.h"
#include "../../services/service_locator.h"
#include "../../input/input_manager.h"

void TalentScreen::render() {

	int screen_width = static_cast<float>(terminal_state(TK_WIDTH));
	int screen_height = static_cast<float>(terminal_state(TK_HEIGHT));

	// selections
	DrawUtils::Box selection_box = DrawUtils::Box(
		0.0f,
	 	0.0f,
		screen_width * 0.25f - 1.0f,
		screen_height - 1.0f
	);
	DrawUtils::draw_box_heavy(selection_box);
	terminal_print(selection_box.x + 1, 0, "Select a Talent");

	// descriptions
	DrawUtils::Box desc_box = {
		selection_box.width + 1.0f,
		0.0f,
		screen_width - selection_box.width - 2.0f,
		screen_height - 1.0f
	};
	DrawUtils::draw_box_heavy(desc_box);
	terminal_print(desc_box.x + 1, 0, "Description");
}

void TalentScreen::update() {

	
}
