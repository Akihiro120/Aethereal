#include "naming.h"
#include "../../../context/context.h"
#include "../world/world.h"
#include "../../../ecs/components/player_component.h"
#include "../../../ecs/components/name_component.h"
#include "../../../ecs/components/level_component.h"

namespace Screens {

	 void MainMenu_Naming::render() {
		  auto& rf = Context::get_render_framework();
		  rf.draw_text("Enter your Name");
		  rf.draw_line(15, false);
		  rf.draw_text(mName);

		  // reset
		  rf.clear();
	 }

	 void MainMenu_Naming::update() {
		  
		  // get keyboard input
		  get_keyboard_input(&mName);

		  if (IsKeyPressed(KEY_ENTER) && !mName.empty()) {

				// create name
				auto& ecs = Context::get_fecs();
				ecs.query_system<PlayerComponent>([&](fecs::EntityID id, PlayerComponent& player) {
					 
					 // attach
					 ecs.add(id, NameComponent(mName));
					 ecs.add(id, LevelComponent());
				});
				
				Context::get_screen_manager().pop();
				Context::get_screen_manager().push(std::make_shared<Screens::World>());
		  }
	 }
}
