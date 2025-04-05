#pragma once

class Screen {
public:
	Screen() = default;

	// screen operations
	virtual void update();
	virtual void render();
};
