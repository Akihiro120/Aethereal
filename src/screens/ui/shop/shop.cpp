#include "shop.h"
#include "../../../context/context.h"
#include "../main_menu/menu.h"

namespace Screens {
	 
	 Shop::Shop() {
		  mOptions = {
				"Exit"
		  };
	 }

	 void Shop::render() {

		  auto& rf = Context::get_render_framework();

		  rf.draw_line(15, false);
		  rf.draw_text("Shop");
		  rf.draw_line(15, false);
		  rf.draw_menu(mOptions, &mSelection);

		  // reset the screen
		  rf.clear();
	 }

	 void Shop::update() {
		  menu_selection_clamped(&mSelection, mOptions.size() - 1);

		  // handle input
		  if (IsKeyPressed(KEY_ENTER)) {
				
				switch (mSelection) {
					 case 0: {
						  auto scr = Context::get_screen_manager().get_previous_screen();

						  Context::get_screen_manager().pop();
						  Context::get_screen_manager().push(scr);
						  break;
					 }
				}
		  }
	 }
}
