#pragma once
#include "../screens/screen_manager/screen_manager.h"
#include "../game_state/game_state.h"
#include <fecs/FECS.h>

class Context {
public:
	 // return screen manager
	 static ScreenManager& get_screen_manager() {
		  return get().mScreenManager;
	 }

	 // return game state
	 static GameState& get_game_state() {
		  return get().mGameState;
	 }

	 // return fecs
	 static fecs::FECS& get_fecs() {
		  return get().mFECS;
	 }

private:
	 Context() {
		  mScreenManager = ScreenManager();
		  mGameState = GameState();
		  mFECS = fecs::FECS();
	 }

	 static Context& get() {
		  static Context instance;
		  return instance;
	 }

	 ScreenManager mScreenManager;
	 GameState mGameState;
	 fecs::FECS mFECS;
};
