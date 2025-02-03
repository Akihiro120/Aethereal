#pragma once

class GameState {
public:
	 GameState();

	 void set_game_running(bool run);
	 bool is_game_running();

private:
	 bool mRunning = true;
};
