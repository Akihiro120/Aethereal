#include "world.h"
#include "../../../context/context.h"
#include "../../../ecs/components/player_component.h"
#include "../../../ecs/components/name_component.h"
#include "../../../ecs/components/level_component.h"

namespace Screens {

	 World::World() {
		  mOptions = {
				"Encounter",
				"Shop",
				"Inventory",
				"Quit"
		  };
	 }
	 
	 void World::render() {
		  std::string name;
		  int level;
		  auto& ecs = Context::get_fecs();
		  ecs.query_system<PlayerComponent>([&](fecs::EntityID id, PlayerComponent& player) {

				// get the stats
				name = ecs.get<NameComponent>(id)->name;
				level = ecs.get<LevelComponent>(id)->level;
		  });
		  
		  auto& rf = Context::get_render_framework();
		  rf.draw_line(15, false);
		  rf.draw_text("Name: " + name);
		  rf.draw_text("Lvl: " + std::to_string(level));
		  rf.draw_line(15, false);
		  rf.draw_menu(mOptions, &mSelection);

		  // clear
		  rf.clear();
	 }

	 void World::update() {
		  menu_selection_clamped(&mSelection, mOptions.size() - 1);
	 }
}
