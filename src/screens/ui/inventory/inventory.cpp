#include "inventory.h"
#include "../../../context/context.h"

namespace Screens {

	 Inventory::Inventory() {
	 }

	 void Inventory::render() {

		  auto& rf = Context::get_render_framework();

		  rf.draw_line(15, false);
		  rf.draw_text("Inventory");
		  rf.draw_line(15, false);

		  // render inventory items
		  // limit amount shown on screen by hiding the overflow

		  // reset
		  rf.clear();
	 }

	 void Inventory::update() {

		  if (IsKeyPressed(KEY_ENTER)) {
				
		  }
	 }
}
