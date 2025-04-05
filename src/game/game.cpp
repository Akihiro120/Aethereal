#include "game.h"
#include <BearLibTerminal.h>
#include "../services/service_locator.h"
#include "../input/input_manager.h"
#include "state/game_state.h"
#include "../screen/screen_manager/screen_manager.h"
#include "../screen/main_menu/main_menu.h"

Game::Game() {

	// Initialize terminal
	terminal_open();
	terminal_set("window: size=192x54, title='Aethereal', resizable=true");

	// initialize
	ServiceLocator::provide(std::make_shared<InputManager>());
	ServiceLocator::provide(std::make_shared<GameState>());
	ServiceLocator::provide(std::make_shared<FECS>());
	ServiceLocator::provide(std::make_shared<ScreenManager>());

	ServiceLocator::get_service<ScreenManager>()->push(std::make_shared<MainMenu>());
}

Game::~Game() {
	// Close terminal
	terminal_close();
}

void Game::run() {
	// Main game loop
	while (ServiceLocator::get_service<GameState>()->is_game_running()) {
		update();
		render();
	}
}

void Game::update() {
	// read input
	auto input_mag = ServiceLocator::get_service<InputManager>();
	input_mag->clear_keys();
	if (terminal_has_input()) {
		int input = terminal_read();
		input_mag->add_key(input);
	}

	// escape game
	input_mag->process_input([](int key) {
		if (key == TK_ESCAPE) ServiceLocator::get_service<GameState>()->close_game();
	});

	// update screen manager
	auto screen_manager = ServiceLocator::get_service<ScreenManager>();
	screen_manager->update();
}

void Game::render() {
	// clear terminal
	terminal_clear();

	// render screen manager
	auto screen_manager = ServiceLocator::get_service<ScreenManager>();
	screen_manager->render();

	// render to screen/display
	terminal_refresh();
}
