#include "renderer.h"
#include "raylib/raylib.h"

// global state variables
static int TERMINAL_WIDTH = 0;
static int TERMINAL_HEIGHT = 0;
static int TERMINAL_CELL_WIDTH = 0;
static int TERMINAL_CELL_HEIGHT = 0;

// terminal write functions
void terminal_print(glm::vec2 pos, const std::string& c) {

}

void terminal_put(glm::vec2 pos, int code) {

}

void terminal_color(Color color) {

}

// terminal state functions
int terminal_width() {

}

int terminal_height() {

}

// terminal input functions
bool terminal_has_input() {

}

int terminal_read() {
	return GetKeyPressed();
}

// terminal management functions
void terminal_init(glm::vec2 cells, glm::vec2 screen, const std::string& font_path) {

}

void terminal_close() {

}
