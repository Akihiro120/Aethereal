#include "status_panel.h"
#include "../../services/service_locator.h"
#include <fecs.h>
#include "../../components/player_component.h"
#include "../../components/name_component.h"
#include "../../components/talent_component.h"

void StatusPanel::render(const DrawUtils::Box& box) {
	// status panel
	terminal_color("white");

	auto ecs = ServiceLocator::get_service<FECS>();

	// satus
	DrawUtils::draw_box_heavy(box);
	terminal_color("white");
	terminal_print(box.x + 1, 1, ecs->get<NameComponent>(m_player_reference)->name.c_str());

	// stats
	terminal_print(box.x + 1, 2, "Title");
	terminal_print(box.x + 1, 4, "Health");
	terminal_print(box.x + 1, 5, "Mana");
	terminal_print(box.x + 1, 6, "Stamina");

	// values
	terminal_print(box.x + 10, 2, ecs->get<TalentComponent>(m_player_reference)->talent.c_str());
	terminal_color("green");
	terminal_print(box.x + 10, 4, "100");
	terminal_print(box.x + 10, 5, "100");
	terminal_print(box.x + 10, 6, "100");
}

void StatusPanel::update() {
	// update status panel
	auto ecs = ServiceLocator::get_service<FECS>();
	ecs->query<PlayerComponent>([&](Entity id, auto& _){
		m_player_reference = id;
	});
}
