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
	 void update_focus();
	 void push_previous_screen();

	 std::shared_ptr<Screen> get_previous_screen();

	 // screen operations
	 ftxui::Component get_container();
	 ftxui::Component get_interface();

	 bool is_empty();

private:
	 // container to hold all current screens
	 std::vector<std::shared_ptr<Screen>> mScreens;
	 std::shared_ptr<Screen> mPreviousScreen;
	 ftxui::Component mContainer;
};
