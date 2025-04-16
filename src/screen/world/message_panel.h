#pragma once
#include "../utilities/draw_utilities.h"
#include "../../game/state/game_state.h"

class MessagePanel {
public:
	MessagePanel();

	void render(const DrawUtils::Box& box);
	void update();

private:
	std::shared_ptr<GameState> m_game_state;
};
