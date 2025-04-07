#include "game_panel.h"

#include "../utilities/draw_utilities.h"

GamePanel::GamePanel() {
	// initialize game panel
	m_world_system.generate_world();
}

void GamePanel::render(const DrawUtils::Box& box) {
	// game panel
	terminal_color("white");
	DrawUtils::draw_box_heavy(box);

	// render within bounds of the screen
	m_world_system.render(box);
	m_render_system.render(box);
}

void GamePanel::update() {
	// update game panel
	m_world_system.update();
	m_camera_system.update();
}
