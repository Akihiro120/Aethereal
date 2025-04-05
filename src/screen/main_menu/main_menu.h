#pragma once
#include <BearLibTerminal.h>
#include "../screen.h"
#include "../../services/service_locator.h"
#include "../../input/input_manager.h"
#include <array>

class MainMenu : public Screen {
public:
	MainMenu() = default;

	void render() override;
	void update() override;

private:
	int m_selected_option = 0;
	std::array<std::string, 2> m_options = {
		"Start Game",
		"Exit"
	};
};
