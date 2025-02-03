#pragma once
#include <string>
#include <vector>
#include <raylib.h>

namespace FWRender {

	 class RenderFramework {
	 public:
		  RenderFramework();

		  // render functions
		  void clear();
		  void draw_text(const std::string& str);
		  void draw_menu(std::vector<std::string> options, int* selection);
		  void draw_line(int size, bool vertical);
		  void set_offset(int new_offset);
		  void new_line();

	 private:
		  int mOffset = 0;
		  Font mFont;
	 };
}
