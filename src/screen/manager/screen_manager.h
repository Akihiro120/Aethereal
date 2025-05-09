#pragma once
#include <ftxui/component/component.hpp>

// Aethereal
#include "../screen_base.h"

using namespace ftxui;

namespace Aethereal::Screen
{
    class ScreenManager
    {
    public:
        Component GetRootComponent();

    private:
        std::vector<std::unique_ptr<ScreenBase>> m_Screens;
    };
}
