#pragma once
#include <fecs.h>

class Game {
public:
	Game();
	~Game();

	void run();

private:
	void update();
	void render();

	FECS mWorld;
	// systems
};
