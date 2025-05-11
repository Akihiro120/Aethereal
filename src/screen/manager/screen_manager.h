#pragma once

// Aethereal
#include "../screen_base.h"
#include <memory>
#include <vector>

namespace Aethereal::Screen
{
    class ScreenManager
    {
    public:
        void Replace(std::shared_ptr<ScreenBase> scr);
        void Overlay(std::shared_ptr<ScreenBase> scr);
        void Pop();

        void Render();
        void Update();

    private:
        std::vector<std::shared_ptr<ScreenBase>> m_Screens;
    };
}
