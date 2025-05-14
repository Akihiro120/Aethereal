#pragma once
#include "../../screen_base.h"
#include "../../../services/injector/injector.h"
#include "../../manager/screen_manager.h"
#include "../../../game/state/game_state.h"
#include <vector>
#include <string>

namespace Aethereal::Screen
{
    namespace MainMenu
    {
        class Menu : public ScreenBase,
                     public Service::Injector<Menu, ScreenManager, State::GameState>
        {
        public:
            Menu();
            ~Menu();

            virtual ftxui::Component CreateComponentRoot() override;
            virtual ftxui::Component CreateComponentContainer() override;

        private:
            ftxui::Component m_OptionsMenu;
            std::vector<std::string> m_Options;
            int m_Selection = 0;
        };
    }
}
