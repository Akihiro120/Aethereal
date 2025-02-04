#include "screen.h"
#include "../math/math.h"

void Screen::render() {
}

void Screen::update() {

}

void Screen::menu_selection_clamped(int* selection, int max) {
	 
	 if (IsKeyPressed(KEY_UP)) {
		  *selection = FWMath::clamp(*selection - 1, 0, max);
	 }
	 if (IsKeyPressed(KEY_DOWN)) {
		  *selection = FWMath::clamp(*selection + 1, 0, max);
	 }

}

void Screen::get_keyboard_input(std::string* text) {
	bool upper;
	if (IsKeyDown(KEY_LEFT_SHIFT))
	{
		upper = true;
	}
	else {
		upper = false;
	}

	if (!IsKeyPressed(KEY_BACKSPACE) && !IsKeyPressed(KEY_LEFT_CONTROL) && !IsKeyPressed(KEY_ENTER))
	{
		int key = GetKeyPressed();
		if (key != 0 && text->length() < 64 - 1) {
			// Append the typed character to the text
			if (upper)
			{
				text->push_back(static_cast<char>(key));
				if (IsKeyPressed(KEY_LEFT_SHIFT))
				{
					text->erase(text->length() - 1);
				}
			}
			else if(!IsKeyPressed(KEY_LEFT_SHIFT)) {
				text->push_back(static_cast<char>(tolower(key)));
			}
		}
	}

	// Clear the input buffer
	if (IsKeyPressed(KEY_BACKSPACE) && text->length() > 0) {
		text->erase(text->length() - 1);
	}
}

void Screen::menu_navigation_2d(Vector2* dimensions, Vector2 max) {

}
