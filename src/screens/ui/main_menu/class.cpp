#include "class.h"

namespace Screens {
	 
	 Class::Class() {
		  using namespace ftxui;

		  // get data 

		  mContainer = ftxui::Container::Vertical({});
		  mInterface = ftxui::Renderer([&]{
				return vbox({
					 text("Select your Class") | bold,
					 separatorHeavy() | size(WIDTH, EQUAL, 50),
					 // display classes

					 separatorHeavy() | size(WIDTH, EQUAL, 50),
					 // display descriptions
				});
		  });
	 }
}
