#pragma once
#include <chrono>
#include <vector>
#include <string>

class GameState {
public:
	GameState();

	void close_game();
	bool is_game_running();

	// time based
	double get_delta_time() const;
	double get_frame_time() const;
	double get_time() const;
	void calculate_time();
	void end_time();

	void set_delta_time(double delta_time);
	void set_frame_time(double frame_time);
	void set_time(double time);

    // ingame logging
    void log(const std::string& message);
    std::vector<std::string> get_log() const;

private:
	bool m_game_running = true;

	// time based
	std::chrono::high_resolution_clock::time_point m_last_time;
	double m_delta_time = 0.0;
	double m_time = 0.0;
	double m_accumulated_time = 0.0;
	double m_frame_time = 0.0;
	double m_frame_count = 0.0;
	uint32_t m_frame_cap = 60;

    // logging
    std::vector<std::string> m_log;
};
