#include "menu.h"
#include "naming.h"
#include "../../../ecs/components/player_component.h"
#include "naming.h"

namespace Screens {
	 MainMenu::MainMenu() {

		  mComponents.push_back(ftxui::Menu(ftxui::MenuOption{
				.entries = std::vector<std::string>{
					 "New Game",
					 "Continue",
					 "Exit"
				},
				.selected = &mSelection,
				.on_enter = [&] {
					 
					 // new game
					 if (mSelection == 0) {
						  Context::get_screen_manager().pop();
						  Context::get_screen_manager().push(std::make_shared<MainMenu_Naming>());
					 }

					 // exit
					 if (mSelection == 2) {
						  Context::get_game_state().set_game_running(false);
					 }
				},
		  }));

		  mContainer = ftxui::Container::Vertical({mComponents[0]});
		  mInterface = ftxui::Renderer([&]{
				return ftxui::vbox({
					 ftxui::text("Aethereal") | ftxui::bold,
					 ftxui::separatorHeavy(),
					 mComponents[0]->Render()
				});
		  });
	 }
}
