#pragma once
#include "../../screen.h"
#include <raymath.h>
#include "../../../context/context.h"

namespace Screens {
	 class MainMenu : public Screen {
	 public:
		  MainMenu();

	 private:
		  int mSelection = 0;
	 };
}
