#include "render_framework.h"

namespace FWRender {
	 RenderFramework::RenderFramework() {
		  mFont = LoadFontEx("../resources/fonts/Consolas.ttf", 16, nullptr, 0);
	 }

	 // render functions
	 void RenderFramework::clear() {
		  mOffset = 0;
	 }
	 void RenderFramework::draw_text(const std::string& str) {
		  float font_size = mFont.baseSize;
		  Vector2 position = {0.0f, font_size * mOffset};
		  
		  DrawTextEx(mFont, str.c_str(), position, font_size, 1, WHITE);

		  mOffset += 1;
	 }

	 void RenderFramework::draw_menu(std::vector<std::string> options, int* selection) {

		  for (int i = 0; i < options.size(); i++) {
				
				std::string decoration = "";
				if (*selection == i) {
					 decoration = " <";
				}

				draw_text(options[i] + decoration);
		  }
	 }

	 void RenderFramework::draw_line(int size, bool vertical) {
		  
		  // start
		  std::string line = "+";
		  if (vertical) {
				line += "\n";
		  }

		  // line
		  for (int i = 0; i < size - 2; i++) {
				if (vertical) {
					 line += "|\n";
				} else {
					 line += "-";
				}
		  }

		  // end
		  line += "+";

		  // render
		  draw_text(line);
	 }

	 void RenderFramework::set_offset(int new_offset) {
		  mOffset = new_offset;
	 }

	 void RenderFramework::new_line() {
		  mOffset++;
	 }

}

