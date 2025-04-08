#include "input_manager.h"

void InputManager::add_key(int key) {
	m_keys.push_back(key);
}

void InputManager::clear_keys() {
	m_keys.clear();
}

void InputManager::process_input(std::function<void(int)> fn) {
	for (auto input : m_keys) {
		fn(input);
	}
}

void InputManager::process_keyboard_input(std::string* s) {
	for (auto key : m_keys) {
		if (key >= TK_A && key <= TK_Z) {
				*s += 'a' + (key - TK_A);
		}
		if (key >= TK_1 && key <= TK_9) {
			*s += '1' + (key - TK_1);
		}
		if (key == TK_0) {
			*s += '0';
		}
		if (key == TK_SPACE) {
			*s += ' ';
		}
		if (key == TK_BACKSPACE && !s->empty()) {
			s->pop_back();
		}
		switch (key) {
			case TK_COMMA: *s += ','; break;
			case TK_MINUS: *s += '-'; break;
		}
	}
}
