#pragma once
#include <string>
#include <vector>
#include "../../screen.h"

namespace Screens {
	 class World : public Screen {
	 public:
		  World();

		  virtual void render();
		  virtual void update();

	 private:
		  std::vector<std::string> mOptions;
		  int mSelection = 0;
	 };
}
