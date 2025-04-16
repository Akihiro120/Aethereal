#pragma once
#include "../screen.h"
#include "game_panel.h"
#include "status_panel.h"
#include "message_panel.h"

class WorldScreen : public Screen {
public:
	WorldScreen();

	void render() override;
	void update() override;

private:
	void init();
	
	// panels
	GamePanel m_game_panel;
	StatusPanel m_status_panel;
	MessagePanel m_message_panel;

};
