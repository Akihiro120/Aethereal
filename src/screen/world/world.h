#pragma once
#include "../screen.h"
#include "game_panel.h"
#include "status_panel.h"
#include "message_panel.h"

class World : public Screen {
public:
	World() = default;

	void render() override;
	void update() override;

private:
	GamePanel m_game_panel;
	StatusPanel m_status_panel;
	MessagePanel m_message_panel;
};
