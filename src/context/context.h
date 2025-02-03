#pragma once
#include "../screens/screen_manager/screen_manager.h"
#include "../render_framework/render_framework.h"
#include "../game_state/game_state.h"
#include <fecs/FECS.h>

class Context {
public:
	 // return screen manager
	 static ScreenManager& get_screen_manager() {
		  return get().mScreenManager;
	 }

	 // return render framework
	 static FWRender::RenderFramework& get_render_framework() {
		  return get().mRenderFramework;
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
		  mRenderFramework = FWRender::RenderFramework();
		  mGameState = GameState();
		  mFECS = fecs::FECS();
	 }

	 static Context& get() {
		  static Context instance;
		  return instance;
	 }

	 ScreenManager mScreenManager;
	 GameState mGameState;
	 FWRender::RenderFramework mRenderFramework;
	 fecs::FECS mFECS;
};
