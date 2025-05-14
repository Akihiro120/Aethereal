#include "menu.h"
#include "naming.h"
#include <ftxui/component/component.hpp>

using namespace ftxui;

namespace Aethereal::Screen
{
    namespace MainMenu
    {

        Menu::Menu()
            : m_Options({"New Game",
                         "Continue",
                         "Options",
                         "Exit"})
        {
            ScreenBase::ConstructSceneRoot();
        }

        Menu::~Menu()
        {
        }

        ftxui::Component Menu::CreateComponentRoot()
        {
            MenuOption options = {
                .on_enter = [this]
            {
                if (m_Selection == 0)
                {
                    GetInjection<ScreenManager>()->Replace(std::make_shared<Naming>());
                }
                if (m_Selection == 3)
                {
                    GetInjection<State::GameState>()->StopRunning();
                }
            },
            };
            m_OptionsMenu = ftxui::Menu(&m_Options, &m_Selection, options);

            return ftxui::Renderer(m_OptionsMenu, [&]()
            {
                return vbox({ftxui::text("Aethereal") | bold,
                             m_OptionsMenu->Render()});
            });
        }

        ftxui::Component Menu::CreateComponentContainer()
        {
            return m_OptionsMenu; // ftxui::Container::Vertical({m_OptionsMenu});
        }
    }
}
