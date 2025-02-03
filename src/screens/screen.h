#pragma once
#include <raylib.h>
#include <string>

class Screen {
public:
	 Screen() = default;

	 // screen oeprations
	 virtual void render();
	 virtual void update();

protected:

	 // operation helpers
	 void menu_selection_clamped(int* selection, int max);
	 void get_keyboard_input(std::string* text);

};
