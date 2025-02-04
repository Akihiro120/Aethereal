#pragma once
#include <vector>
#include <string>
#include "../../screen.h"

namespace Screens {
	 
	 class Shop : public Screen {
	 public:
		  Shop();

		  virtual void render();
		  virtual void update();
		  
	 private:
		  int mSelection = 0;
		  std::vector<std::string> mOptions;
	 };
}
