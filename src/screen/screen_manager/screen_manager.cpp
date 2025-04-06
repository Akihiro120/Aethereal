#include "screen_manager.h"

void ScreenManager::push(std::shared_ptr<Screen> screen) {
	m_screens.push_back(screen);
}

void ScreenManager::pop() {
	if (!m_screens.empty()) {
		m_screens.pop_back();
	}
}

void ScreenManager::update() {
	if (!m_screens.empty()) {
		m_screens[m_screens.size() - 1]->update();
	}
}

void ScreenManager::render() {
	for (auto& screen : m_screens) {
		screen->render();
	}
}

void ScreenManager::transition(std::shared_ptr<Screen> screen) {
	m_screens.clear();
	m_screens.push_back(screen);
}

