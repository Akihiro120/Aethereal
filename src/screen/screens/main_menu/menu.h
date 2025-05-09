#pragma once
#include "../../screen_base.h"
#include <vector>

namespace Aethereal::Screen
{
    namespace MainMenu
    {
        class Menu : public Aethereal::Screen::ScreenBase
        {
        public:
            Menu();
            ~Menu();

        private:
            Component CreateSceneRoot();

            // Option Menu
            Component m_OptionMenu;
            std::vector<std::string> m_Options;
            int m_OptionMenuSelection = 0;
        };
    }
}
