#include "naming.h"
#include "../../../context/context.h"
#include "../world/world.h"
#include "../../../ecs/components/player_component.h"
#include "../../../ecs/components/name_component.h"
#include "../../../ecs/components/level_component.h"

namespace Screens {

	 MainMenu_Naming::MainMenu_Naming() {
		  mComponents.push_back(ftxui::Input(ftxui::InputOption{
				.content = &mName,
				.multiline = false,
				.on_enter = [&] {

				}
		  })); 

		  mContainer = ftxui::Container::Vertical({mComponents[0]});
		  mInterface = ftxui::Renderer([&]{
				return ftxui::vbox({
					 ftxui::text("Name your Character") | ftxui::bold,
					 ftxui::separatorHeavy(),
					 mComponents[0]->Render()
				});
		  });

	 }
}
