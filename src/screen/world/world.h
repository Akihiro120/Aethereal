#pragma once
#include "../screen.h"
#include "game_panel.h"
#include "status_panel.h"
#include "message_panel.h"
#include "systems/player_systems.h"
#include "systems/physics_system.h"

class World : public Screen {
public:
	World();

	void render() override;
	void update() override;

private:
	void init();
	
	// panels
	GamePanel m_game_panel;
	StatusPanel m_status_panel;
	MessagePanel m_message_panel;

	// systems
	PlayerSystem m_player_system;
	PhysicsSystem m_physics_system;
};
