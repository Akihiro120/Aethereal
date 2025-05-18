#pragma once

// Aethereal
#include <memory>
#include <vector>
#include "../../services/injector/injector.h"
#include "../screen_base.h"

namespace Aethereal::State
{
    class GameState;
}

namespace Aethereal::Screen
{

    class ScreenManager
    {
    public:
        ScreenManager();
        void Replace(std::shared_ptr<ScreenBase> scr);
        void Overlay(std::shared_ptr<ScreenBase> scr);
        void Pop();

        void Render();
        void Update();
        bool IsClosed();
        void Clean();

    private:
        std::vector<std::shared_ptr<ScreenBase>> m_Screens;
    };
}
