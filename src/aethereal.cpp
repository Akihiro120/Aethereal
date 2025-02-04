#include "aethereal.h"
#include "context/context.h"
#include "screens/screen_manager/screen_manager.h"
#include "screens/ui/main_menu/menu.h"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/loop.hpp>

Aethereal::Aethereal() {
	 
}

void Aethereal::run() {
	 // managers
	 auto& sm = Context::get_screen_manager();
	 Context::get_screen_manager().push(std::make_shared<Screens::MainMenu>());

	 // ftxui window
	 auto screen = ftxui::ScreenInteractive::Fullscreen();
	 auto interface = ftxui::Renderer(sm.get_container(), [&] {

	   // empty
	   if (sm.is_empty()) {
	 		return ftxui::text("Empty Scene") | ftxui::bold; 
	   }

	   return sm.get_interface()->Render(); 
	 }) | ftxui::bgcolor(ftxui::Color::Black);

	 // loop
	 auto loop = ftxui::Loop(&screen, interface);

	 // render _loop
	 while (!loop.HasQuitted() && Context::get_game_state().is_game_running()) {
		  // render
		  loop.RunOnce();

		  std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
		  screen.PostEvent(ftxui::Event::Custom);
	 }
}

void Aethereal::clean_up() {

}
