#include "world.h"
#include "../utilities/draw_utilities.h"

void World::render() {
	// screen dimensions
	int screen_width = terminal_state(TK_WIDTH)-1;
	int screen_height = terminal_state(TK_HEIGHT)-1;

	m_game_panel.render(DrawUtils::Box(0.0f, 0.0f, screen_width*0.75f-1, (float)screen_height));
	m_status_panel.render(DrawUtils::Box(screen_width*0.75f, 0.0f, screen_width*0.25f, screen_height*0.75f-1));
	m_message_panel.render(DrawUtils::Box(screen_width*0.75f, screen_height*0.75f, screen_width*0.25f, screen_height*0.25f));
}

void World::update() {
}
