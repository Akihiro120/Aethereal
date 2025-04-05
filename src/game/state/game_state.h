#pragma once

class GameState {
public:
	GameState() = default;

	void close_game();
	bool is_game_running();

private:
	bool m_game_running = true;
};
