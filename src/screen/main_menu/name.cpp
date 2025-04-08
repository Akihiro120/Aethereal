#include "name.h"
#include <BearLibTerminal.h>
#include "../../data/enums/unicodes.h"
#include "../../services/service_locator.h"
#include "../../input/input_manager.h"
#include "../screen_manager/screen_manager.h"
#include "talent.h"

void NameScreen::render() {
	terminal_color("white");	
	terminal_print(0, 0, "Name your Character:");
	
	for (int i = 0; i < 15; i++) {
		terminal_put(i, 1, (int)Unicode::BoxHeavy::HORIZONTAL);
	}

	if (m_name.size() > 0) {
		terminal_color("white");
		terminal_print(0, 2, (m_name + "_").c_str());
	} else {
		terminal_color("grey");
		terminal_print(0, 2, "Enter name...");
	}
}

void NameScreen::update() {
	auto input_mag = ServiceLocator::get_service<InputManager>();
	input_mag->process_keyboard_input(&m_name);
	input_mag->process_input([this](int key) {
		if (key == TK_ENTER && m_name.size() > 0) {
			auto screen_manager = ServiceLocator::get_service<ScreenManager>();	
			screen_manager->transition(std::make_shared<TalentScreen>());
		}
	});
}
