#include "game_state.h"

GameState::GameState() {

}

bool GameState::is_game_running() {
	 return mRunning;
}

void GameState::set_game_running(bool run) {
	 mRunning = run;
}
