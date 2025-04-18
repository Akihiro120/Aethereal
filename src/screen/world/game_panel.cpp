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
	auto input = ServiceLocator::get_service<InputManager>();
	input->process_input([this](int key) {

		// process input for player movement
		m_player_system.movement(key);
        m_player_system.inventory(key);
        m_player_system.harvest(key);
	});

    // run systems
	m_physics_system.calculate_spatial_map();
	m_physics_system.resolve_collisions();
	m_physics_system.resolve_velocities();
    m_harvesting_system.harvest();
    m_inventory_system.update();
	m_world_system.update();
	m_camera_system.update();
}
