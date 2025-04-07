#include "main_menu.h"
#include <glm/glm.hpp>
#include "../../data/enums/unicodes.h"
#include "../../services/service_locator.h"
#include "../../input/input_manager.h"
#include "../../game/state/game_state.h"
#include "../../screen/screen_manager/screen_manager.h"
#include "../world/world.h"

void MainMenu::render() {
	terminal_color("white");
	terminal_print(0, 0, "Aethereal");
	for (int i = 0; i < 15; i++) {
		terminal_put(i, 1, (int)Unicode::BoxHeavy::HORIZONTAL);
	}

	// Draw the menu options
	for (int i = 0; i < m_options.size(); ++i) {
		terminal_color("white");
		if (i == m_selected_option) {
			terminal_color("yellow");
		}
		terminal_print(0, 2 + i, m_options[i].c_str());
	}

	terminal_color("grey");
	terminal_print(0, terminal_state(TK_HEIGHT) - 1, "Press ESC to exit");
}

void MainMenu::update() {
	
	auto input_mag = ServiceLocator::get_service<InputManager>();
	input_mag->process_input([this](int key) {
		if (key == TK_UP || key == TK_K) {
			m_selected_option = glm::clamp(m_selected_option - 1, 0, (int)m_options.size() - 1);
		}

		if (key == TK_DOWN || key == TK_J) {
			m_selected_option = glm::clamp(m_selected_option + 1, 0, (int)m_options.size() - 1);
		}

		if (key == TK_ENTER) {
			auto game_state = ServiceLocator::get_service<GameState>();
			if (m_selected_option == 0) {
				auto scr_manager = ServiceLocator::get_service<ScreenManager>();
				scr_manager->pop();
				scr_manager->push(std::make_shared<WorldScreen>());
			}
			else if (m_selected_option == 1) {
				// Exit game
				game_state->close_game();
			}
		}
	});
}
