#include "game_state.h"

void GameState::close_game() {
	m_game_running = false;
}

bool GameState::is_game_running() {
	return m_game_running;
}
