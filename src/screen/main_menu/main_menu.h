#pragma once
#include <BearLibTerminal.h>
#include "../screen.h"

class MainMenu : public Screen {
public:
	MainMenu() = default;

	void render() override {
		terminal_color("white");
		terminal_print(0, 0, "Aethereal");
		terminal_print(0, 1, "Start Game"); 

		terminal_color("grey");
		terminal_print(1, terminal_state(TK_HEIGHT) - 1, "Press ESC to exit");
	}

	void update() override {
	
	}

private:
};
