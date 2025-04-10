#include "talent.h"
#include <BearLibTerminal.h>
#include "../utilities/draw_utilities.h"
#include "../../data/database/database.h"
#include "../../services/service_locator.h"
#include "../../input/input_manager.h"
#include "../screen_manager/screen_manager.h"
#include "../world/world.h"
#include <glm/glm.hpp>
#include <memory>

void TalentScreen::render() {

	int screen_width = static_cast<float>(terminal_state(TK_WIDTH));
	int screen_height = static_cast<float>(terminal_state(TK_HEIGHT));

	// selections
	terminal_color("white");
	DrawUtils::Box selection_box = DrawUtils::Box(
		0.0f,
	 	0.0f,
		screen_width * 0.25f - 1.0f,
		screen_height - 1.0f
	);
	DrawUtils::draw_box_heavy(selection_box);
	terminal_print(selection_box.x + 1, 0, "Select a Talent");

	auto db = ServiceLocator::get_service<Database>();
	auto talents = db->get_json("talent")->at("talents");
	m_num_talents = talents.size();
	// operations
	for (int i = 0; i < m_num_talents; ++i) {
		std::string name = talents[i]["name"];

		terminal_color("white");
		if (m_selected == i) {
			terminal_color("yellow");
		}
		terminal_print(1, 1 + i, name.c_str());
	}

	// descriptions
	DrawUtils::Box desc_box = {
		selection_box.width + 1.0f,
		0.0f,
		screen_width - selection_box.width - 2.0f,
		screen_height - 1.0f
	};
	terminal_color("white");
	DrawUtils::draw_box_heavy(desc_box);
	terminal_print(desc_box.x + 1, 0, "Description");
	// name
	terminal_print(desc_box.x + 1, 1, ((std::string)talents[m_selected].at("name")).c_str());

	// desc
	auto desc_wrapped = DrawUtils::wrap_text((std::string)talents[m_selected].at("description"), 80);
	for (int i = 0; i < desc_wrapped.size(); i++) {
		terminal_print(desc_box.x + 1, 3 + i, desc_wrapped[i].c_str());
	}

	// flavor
	terminal_color("grey");
	auto flavor_wrapped = DrawUtils::wrap_text(
		"\"" + (std::string)talents[m_selected].at("flavor") + "\"" + "- ???", 
	80);
	for (int i = 0; i < flavor_wrapped.size(); i++) {
		terminal_print(desc_box.x + 1, 4 + desc_wrapped.size() + i, flavor_wrapped[i].c_str());
	}
}

void TalentScreen::update() {

	auto input_mag = ServiceLocator::get_service<InputManager>();
	input_mag->process_input([this](int key) {
		if (key == TK_UP || key == TK_K) {
			m_selected = glm::clamp(m_selected - 1, 0, m_num_talents - 1);
		}

		if (key == TK_DOWN || key == TK_J) {
			m_selected = glm::clamp(m_selected + 1, 0, m_num_talents - 1);
		}

		if (key == TK_ENTER) {
			auto sm = ServiceLocator::get_service<ScreenManager>();
			sm->transition(std::make_shared<WorldScreen>());
		}
	});
	
}
