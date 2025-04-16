#include "game_state.h"
#include <chrono>
#include <thread>

GameState::GameState() :
	m_last_time(std::chrono::high_resolution_clock::now()),
	m_delta_time(0.0),
	m_frame_time(0.0),
	m_time(0.0),
	m_frame_cap(120.0),
	m_accumulated_time(0.0), // Initialize accumulated time
	m_frame_count(0)
{
}

void GameState::close_game() {
	m_game_running = false;
}

bool GameState::is_game_running() {
	return m_game_running;
}

double GameState::get_delta_time() const {
	return m_delta_time;
}

double GameState::get_frame_time() const {
	return m_frame_time;
}

double GameState::get_time() const{
	return m_time;	
}

void GameState::set_delta_time(double delta_time) {
	m_delta_time = delta_time;
}

void GameState::set_frame_time(double frame_time) {
	m_frame_time = frame_time;
}

void GameState::set_time(double time) {
	m_time = time;
}

void GameState::calculate_time() {
	auto now = std::chrono::high_resolution_clock::now();
	m_delta_time = std::chrono::duration<double>(now - m_last_time).count();
 	m_last_time = now;

 	m_time += m_delta_time;

 	m_accumulated_time += m_delta_time;
 	m_frame_count++;

 	if (m_accumulated_time >= 1.0) {
	  	m_frame_time = m_frame_count;
	  	m_frame_count = 0;
	  	m_accumulated_time -= 1.0;
 	}
}

void GameState::end_time() {
	// Target duration for one frame
   auto frame_duration = std::chrono::milliseconds(static_cast<int>(1000 / m_frame_cap));
    
   // Calculate actual time spent in the current frame
   auto now = std::chrono::high_resolution_clock::now();
   auto time_spent = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_last_time);

   // Calculate remaining time to sleep
   if (time_spent < frame_duration) {
      std::this_thread::sleep_for(frame_duration - time_spent);
   }
}
