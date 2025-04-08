#pragma once
#include <BearLibTerminal.h>
#include <functional>
#include <vector>
#include <string>

class InputManager {
public:
	InputManager() = default;

	void add_key(int key);
	void clear_keys();
	void process_input(std::function<void(int)> fn);
	void process_keyboard_input(std::string* input);

private:
	std::vector<int> m_keys;
};
