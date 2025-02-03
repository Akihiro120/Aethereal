#pragma once
#include <vector>
#include <memory>
#include "../screen.h"

/**
using a stack based approach to work with the screens
**/

class ScreenManager {
public:
	 ScreenManager();

	 // screen manipulation
	 void push(std::shared_ptr<Screen> screen);
	 void pop();

	 // screen operations
	 void update();
	 void render();

	 bool is_empty();

private:
	 // container to hold all current screens
	 std::vector<std::shared_ptr<Screen>> mScreens;
};
