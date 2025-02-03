#pragma once
#include "../../screen.h"
#include "../../../context/context.h"

namespace Screens {
	 class MainMenu_Naming : public Screen {
	 public:
		  MainMenu_Naming() = default;

		  virtual void render();
		  virtual void update();

	 private:
		  std::string mName = "";
	 };
}
