#pragma once
#include "../utilities/draw_utilities.h"
#include "systems/render_systems.h"
#include "systems/world_system.h"
#include "systems/camera_system.h"
#include "systems/harvesting_system.h"
#include "systems/inventory_system.h"
#include "systems/player_systems.h"
#include "systems/physics_system.h"

class GamePanel {
public:
	GamePanel();

	void render(const DrawUtils::Box& box);
	void update();

private:
	WorldSystem m_world_system;
	RenderSystem m_render_system;
	CameraSystem m_camera_system;
	PlayerSystem m_player_system;
	PhysicsSystem m_physics_system;
    HarvestingSystem m_harvesting_system;   
    InventorySystem m_inventory_system;
};
