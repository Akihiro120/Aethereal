#include "menu.h"
#include "naming.h"
#include "../../../ecs/components/player_component.h"
#include "naming.h"

namespace Screens {
	 MainMenu::MainMenu() {
		  using namespace ftxui;

		  auto menu_option = MenuOption::Vertical();
		  menu_option.entries = std::vector<std::string>{
					 "New Game",
					 "Continue",
					 "Exit"
		  };
		  menu_option.selected = &mSelection;
		  menu_option.on_enter = [&] {
				// new game
				if (mSelection == 0) {
					 Context::get_screen_manager().pop();
					 Context::get_screen_manager().push(std::make_shared<MainMenu_Naming>());
				}

				// exit
				if (mSelection == 2) {
					 Context::get_game_state().set_game_running(false);
				}
		  };
		  mComponents.push_back(Menu(menu_option));

		  mContainer = Container::Vertical({mComponents[0]});
		  mInterface = Renderer([&]{
				return vbox({
					 text("Aethereal") | bold,
					 separatorHeavy() | size(WIDTH, EQUAL, 50),
					 mComponents[0]->Render() | size(WIDTH, EQUAL, 10)
				});
		  });
	 }
}
