#include "screen_manager.h"

ScreenManager::ScreenManager() {

}

void ScreenManager::push(std::shared_ptr<Screen> screen) {
	 mScreens.push_back(screen);
}

void ScreenManager::pop() {
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
