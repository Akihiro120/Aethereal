#include "naming.h"
#include "../../../context/context.h"
#include "class.h"
#include "../../../ecs/components/player_component.h"
#include "../../../ecs/components/name_component.h"
#include "../../../ecs/components/level_component.h"

namespace Screens {
	 using namespace ftxui;

	 MainMenu_Naming::MainMenu_Naming() {
		  mComponents.push_back(ftxui::Input(ftxui::InputOption{
				.content = &mName,
				.transform = [&](InputState state) {
					 Element e = text(mName);

					 return e | bold;
				},
				.multiline = false,
				.on_enter = [&] {

					 if (!mName.empty()) {
						  Context::get_screen_manager().pop();
						  Context::get_screen_manager().push(std::make_shared<Class>());
					 }
				}
		  })); 

		  mContainer = ftxui::Container::Vertical({mComponents[0]});
		  mInterface = ftxui::Renderer([&]{
				return ftxui::vbox({
					 ftxui::text("Name your Character") | ftxui::bold,
					 ftxui::separatorHeavy() | size(WIDTH, EQUAL, 50),
					 mComponents[0]->Render() | borderHeavy | size(WIDTH, EQUAL, 50)
				});
		  });

	 }
}
