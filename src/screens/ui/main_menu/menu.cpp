#include "menu.h"
#include "naming.h"
#include "../../../ecs/components/player_component.h"

namespace Screens {
	 MainMenu::MainMenu() {
		  mOptions = {
				"New Game",
				"Continue",
				"Quit"
		  };
	 }

	 void MainMenu::render() {
		  auto& rf = Context::get_render_framework();
		  rf.draw_text("Aethereal");
		  rf.draw_line(15, false);
		  rf.draw_menu(mOptions, &mSelection);

		  // reset
		  rf.clear();
	 }

	 // update method
	 void MainMenu::update() {
		  menu_selection_clamped(&mSelection, mOptions.size() - 1);

		  // options
		  if (IsKeyPressed(KEY_ENTER)) {
				
				switch (mSelection) {
					 
					 case 0: {
						  // create player
						  auto player = Context::get_fecs().add_entity();
						  Context::get_fecs().add(player, PlayerComponent());

						  // change screen
						  Context::get_screen_manager().pop();
						  Context::get_screen_manager().push(std::make_shared<MainMenu_Naming>());
						  break;
					 }
					 case 1: {
						  Context::get_screen_manager().pop();
						  break;
					 }
					 case 2: {
						  // quit
						  Context::get_game_state().set_game_running(false);
						  break;
					 }
				}
		  }
	 }
}
