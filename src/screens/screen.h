#pragma once
#include <ftxui/component/component.hpp>

class Screen {
public:
	 Screen() = default;

	 // screen oeprations
	 ftxui::Component get_container(); 
	 ftxui::Component get_interface(); 

protected:

	 // operation helpers
	 ftxui::Component mContainer;
	 ftxui::Component mInterface;

	 std::vector<ftxui::Component> mComponents;
};
