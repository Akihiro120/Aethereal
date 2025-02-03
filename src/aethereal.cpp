#include "aethereal.h"
#include <raylib.h>
#include "context/context.h"
#include "screens/screen_manager/screen_manager.h"
#include "screens/ui/main_menu/menu.h"

Aethereal::Aethereal() {
	 
	 // begin rendering context
	 InitWindow(1280, 720, "Aethereal");
	 SetTargetFPS(60);
}

void Aethereal::run() {
	 // managers
	 auto& sm = Context::get_screen_manager();
	 sm.push(std::make_shared<Screens::MainMenu>());

	 // render _loop
	 while (!WindowShouldClose() && Context::get_game_state().is_game_running()) {

		  // update
		  sm.update();
		  
		  // render
		  BeginDrawing();
		  ClearBackground(BLACK);

		  // add render operations here
		  if (sm.is_empty()) {
				// render this if the screen is empty
				DrawText("Empty Scene", 0, 0, 16, WHITE);
		  } else {
				// else render the main game
				sm.render();
		  }

		  EndDrawing();
	 }
}

void Aethereal::clean_up() {

	 // end
	 CloseWindow();
}
