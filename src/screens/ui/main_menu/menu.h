#pragma once
#include "../../screen.h"
#include <raymath.h>
#include "../../../context/context.h"

namespace Screens {
	 class MainMenu : public Screen {
	 public:
		  MainMenu();

		  virtual void render();
		  virtual void update();

	 private:
		  std::vector<std::string> mOptions;
		  int mSelection = 0;
	 };
}
