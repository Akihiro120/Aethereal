#include "screen_manager.h"

ScreenManager::ScreenManager() {

}

void ScreenManager::push(std::shared_ptr<Screen> screen) {
	 mScreens.push_back(screen);
}

void ScreenManager::pop() {
	 // save the previous screen
	 mPreviousScreen = mScreens[mScreens.size() - 1];

	 mScreens.pop_back();
}

void ScreenManager::render() {

	 for (auto screen : mScreens) {
		  screen->render();
	 }
}

void ScreenManager::update() {

	 // update the uppermost 
	 if (!is_empty()) {
		  mScreens[mScreens.size() - 1]->update();
	 }
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
