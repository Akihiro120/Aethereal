#pragma once
#include <functional>
#include <vector>

class InputManager {
public:
	InputManager() = default;

	void add_key(int key) {
		m_keys.push_back(key);
	}

	void clear_keys() {
		m_keys.clear();
	}

	void process_input(std::function<void(int)> fn) {
		for (auto input : m_keys) {
			fn(input);
		}
	}

private:
	std::vector<int> m_keys;
};
