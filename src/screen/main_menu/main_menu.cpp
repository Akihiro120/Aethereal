#include "main_menu.h"
#include <glm/glm.hpp>

void MainMenu::render() {
	terminal_color("white");
	terminal_print(0, 0, "Aethereal");

	// Draw the menu options
	for (int i = 0; i < m_options.size(); ++i) {
		terminal_color("white");
		if (i == m_selected_option) {
			terminal_color("yellow");
		}
		terminal_print(0, 1 + i, m_options[i].c_str());
	}

	terminal_color("grey");
	terminal_print(0, terminal_state(TK_HEIGHT) - 1, "Press ESC to exit");
}

void MainMenu::update() {
	
	auto input_mag = ServiceLocator::get_service<InputManager>();
	input_mag->process_input([this](int key) {
		if (key == TK_UP) {
			m_selected_option = glm::clamp(m_selected_option - 1, 0, (int)m_options.size() - 1);
		}

		if (key == TK_DOWN) {
			m_selected_option = glm::clamp(m_selected_option + 1, 0, (int)m_options.size() - 1);
		}
	});
}
