#include "game.h"
#include <BearLibTerminal.h>
#include "../services/service_locator.h"
#include "../input/input_manager.h"
#include "state/game_state.h"
#include "../screen/screen_manager/screen_manager.h"
#include "../screen/main_menu/main_menu.h"
#include "../data/database/database.h"

Game::Game() {

	// Initialize terminal
	terminal_open();
	terminal_set("window: size=160x50, title='Aethereal', resizable=true; font: ../resources/fonts/CascadiaCove.ttf, size=16, hinting=normal;");

	// initialize
	ServiceLocator::provide(std::make_shared<InputManager>());
	ServiceLocator::provide(std::make_shared<GameState>());
	ServiceLocator::provide(std::make_shared<FECS>());
	ServiceLocator::provide(std::make_shared<ScreenManager>());
	ServiceLocator::provide(std::make_shared<Database>());

	ServiceLocator::get_service<Database>()->load_directory("../resources/data/");

	// add main menu starting screen
	ServiceLocator::get_service<ScreenManager>()->push(std::make_shared<MainMenu>());
}

Game::~Game() {
	// Close terminal
	terminal_close();
}

void Game::run() {
	std::shared_ptr<GameState> state = ServiceLocator::get_service<GameState>();

	// Main game loop
	while (state->is_game_running()) {
		state->calculate_time();
		update();
		render();
		/*state->end_time();*/
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
