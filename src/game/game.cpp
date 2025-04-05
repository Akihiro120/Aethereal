#include "game.h"
#include <BearLibTerminal.h>
#include <ApplicationServices/ApplicationServices.h>
#include "../services/service_locator.h"
#include "../input/input_manager.h"
#include "state/game_state.h"

Game::Game() {

	// Initialize terminal
	terminal_open();
	terminal_set("window: size=192x54, title='Aethereal', resizable=true");

	// initialize
	ServiceLocator::provide(std::shared_ptr<InputManager>());
	ServiceLocator::provide(std::shared_ptr<GameState>());
}

Game::~Game() {
	// Close terminal
	terminal_close();
}

void Game::run() {
	// Main game loop
	while (ServiceLocator::get_service<GameState>().is_game_running()) {
		update();
		render();
	}

}

void Game::update() {
	// read input
	auto input_mag = ServiceLocator::get_service<InputManager>();
	input_mag.clear_keys();
	if (terminal_has_input()) {
		int input = terminal_read();
		input_mag.add_key(input);
	}

	// escape game
	input_mag.process_input([](int key) {
		if (key == TK_ESCAPE) ServiceLocator::get_service<GameState>().close_game();
	});
}

void Game::render() {
	terminal_color("white");
	terminal_print(0, 0, "Aethereal");
	terminal_print(0, 1, "Start Game"); 

	terminal_color("grey");
	terminal_print(1, terminal_state(TK_HEIGHT) - 1, "Press ESC to exit");
	terminal_refresh();
}
