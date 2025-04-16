#include "message_panel.h"

#include "../utilities/draw_utilities.h"
#include "../../services/service_locator.h"
#include <glm/glm.hpp>

MessagePanel::MessagePanel() {
	// initialize message panel
	m_game_state = ServiceLocator::get_service<GameState>();	
}

void MessagePanel::render(const DrawUtils::Box& box) {
	// message panel
	terminal_color("white");
	DrawUtils::draw_box_heavy(box);

	int frame_rate = static_cast<int>(m_game_state->get_frame_time());
	terminal_print(box.x + 1, box.y + 1, ("FPS: " + std::to_string(frame_rate)).c_str());

    // draw messages
    terminal_color("grey");
    for (int i = m_msg_offset; i < m_game_state->get_log().size(); ++i) {
        terminal_print(box.x + 1, box.y + 2 + i - m_msg_offset, m_game_state->get_log()[i].c_str());
    }
}

void MessagePanel::update() {
	// update message panel
    // check if the message panel is full
    int limit = 11;
    if (m_game_state->get_log().size() > limit) {
        m_msg_offset = m_game_state->get_log().size() - limit;
    }
}
