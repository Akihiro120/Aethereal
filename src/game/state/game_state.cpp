#include "game_state.h"

namespace Aethereal::State
{
    GameState::GameState()
    {
    }

    bool GameState::IsGameRunning()
    {
        return m_Running;
    }

    void GameState::StopRunning()
    {
        m_Running = false;
    }
}
