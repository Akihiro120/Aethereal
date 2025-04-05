#pragma once
#include <memory>
#include <vector>
#include "../screen.h"

class ScreenManager {
public:
	ScreenManager() = default;

	// screen management
	void push(std::shared_ptr<Screen> screen); 
	void pop();
	/*Screen get_current_screen();*/

	// screen operations
	void render();
	void update();

private:
	std::vector<std::shared_ptr<Screen>> m_screens;
};
