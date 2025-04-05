#pragma once

class ScreenManager {
public:
	ScreenManager() = default;

	// screen management
	void push();
	void pop();
};
