#pragma once
#include "../utilities/draw_utilities.h"
#include "systems/render_systems.h"
#include "systems/world_system.h"
#include "systems/camera_system.h"

class GamePanel {
public:
	GamePanel();

	void render(const DrawUtils::Box& box);
	void update();

private:
	WorldSystem m_world_system;
	RenderSystem m_render_system;
	CameraSystem m_camera_system;
};
