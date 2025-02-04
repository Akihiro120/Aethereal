#include "screen_manager.h"

ScreenManager::ScreenManager() {
	 mContainer = ftxui::Container::Vertical({});
}

void ScreenManager::push(std::shared_ptr<Screen> screen) {
	 mScreens.push_back(screen);
	 update_focus();

}

void ScreenManager::update_focus() {

	 mContainer->DetachAllChildren();
	 mContainer->Add(mScreens[mScreens.size() - 1]->get_container());
}

void ScreenManager::pop() {
	 // save the previous screen
	 mPreviousScreen = mScreens[mScreens.size() - 1];

	 mScreens.pop_back();
}

bool ScreenManager::is_empty() {
	 return mScreens.empty();
}

// pushes the previous screen (state restored)
// into the stack
// The previous screen is the latest that has been popped
void ScreenManager::push_previous_screen() {

	 mScreens.push_back(mPreviousScreen);
}

// returns the last screen
std::shared_ptr<Screen> ScreenManager::get_previous_screen() {
	 return mPreviousScreen;
}

ftxui::Component ScreenManager::get_container() {
	 return mContainer;
}

ftxui::Component ScreenManager::get_interface() {
	 return is_empty() ? ftxui::Container::Vertical({}) : mScreens[mScreens.size() - 1]->get_interface(); 
}
