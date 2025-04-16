#pragma once
#include "../screen.h"
#include <fecs.h>
#include <memory>
#include "../../input/input_manager.h"
#include "../screen_manager/screen_manager.h"
#include "../../game./state/game_state.h"
#include "../utilities/draw_utilities.h"

using namespace DrawUtils;

class InventoryScreen : public Screen {
public:
    InventoryScreen();

    void render() override;
    void update() override;

private:
    std::shared_ptr<FECS> m_ecs;
	std::shared_ptr<InputManager> m_im;
	std::shared_ptr<ScreenManager> m_sm;
    std::shared_ptr<GameState> m_gs;
    Box m_inventory_bounds;

    int m_selected_item = 0;
};
