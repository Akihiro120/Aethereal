#include "world.h"
#include "../utilities/draw_utilities.h"
#include "../../input/input_manager.h"
#include "../../components/camera_component.h"
#include "../../components/player_component.h"
#include "../../components/collider_component.h"
#include "../../components/interaction/input_mode_component.h"
#include "../../components/inventory/inventory_component.h"
#include "BearLibTerminal.h"

WorldScreen::WorldScreen() {
	init();
}

void WorldScreen::render() {

	// screen dimensions
	int screen_width = terminal_state(TK_WIDTH)-1;
	int screen_height = terminal_state(TK_HEIGHT)-1;

	// render the panels
	m_game_panel.render(DrawUtils::Box(0.0f, 0.0f, screen_width*0.75f-1, (float)screen_height));
	m_status_panel.render(DrawUtils::Box(screen_width*0.75f, 0.0f, screen_width*0.25f, screen_height*0.75f-1));
	m_message_panel.render(DrawUtils::Box(screen_width*0.75f, screen_height*0.75f, screen_width*0.25f, screen_height*0.25f));
}

void WorldScreen::init() {
	// initialize player
	auto ecs = ServiceLocator::get_service<FECS>();
	ecs->query<PlayerComponent>([&](Entity id, auto& _) {
		ecs->attach<PositionComponent>(id, PositionComponent(0.0f, 0.0f));
		ecs->attach<VelocityComponent>(id, VelocityComponent(0.0f, 0.0f));
		ecs->attach<RenderComponent>(id, {(int)'@', color_from_name("green")});
		ecs->attach<ColliderComponent>(id, {
			// insert player on_collision logic here
		});
        ecs->attach<InventoryComponent>(id, InventoryComponent{});
        ecs->attach<InputModeComponent>(id, InputModeComponent{InputModeComponent::InputMode::DEFAULT});
	});

	// initialize camera
	Entity camera = ecs->create_entity();
	ecs->attach<CameraComponent>(camera, {0.0f, 0.0f});
}

void WorldScreen::update() {

    // update panels
    m_status_panel.update();
    m_message_panel.update();
	m_game_panel.update();
}
