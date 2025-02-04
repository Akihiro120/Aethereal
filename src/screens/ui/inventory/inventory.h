#pragma once
#include "../../screen.h"
#include "../../../render_framework/render_framework.h"

namespace Screens {
	 
	 class Inventory : public Screen {
	 public:
		  Inventory();

		  virtual void render();
		  virtual void update();

	 private:
		  Vector2 mSelections;
	 };
}
