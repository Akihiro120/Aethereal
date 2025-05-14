#include "naming.h"
#include "../../../components/character/name_component.h"
#include "../../../components/tags/player_component.h"
#include "species.h"
#include <ftxui/component/component.hpp>

using namespace ftxui;

namespace Aethereal::Screen::MainMenu
{
    Naming::Naming()
        : m_ScreenManager(GetInjection<ScreenManager>()),
          m_Registry(GetInjection<FECS::Registry>()),
          m_Name("")
    {
        ConstructSceneRoot();
    }

    ftxui::Component Naming::CreateComponentRoot()
    {
        auto options = InputOption{
            .multiline = false,
            .on_enter = [&]
        {
            if (!m_Name.empty())
            {
                // attach player and name
                auto playerID = m_Registry->CreateEntity();
                m_Registry->Attach(playerID, Components::Tags::PlayerComponent{});
                m_Registry->Attach(playerID, Components::Character::NameComponent{m_Name});

                // Replace the screen
                m_ScreenManager->Replace(std::make_shared<Species>());
            }
        },
        };
        m_NameInput = Input(&m_Name, "Enter your name...", options);

        return Renderer([&]
        {
            return vbox({text("Name your character") | bold,
                         m_NameInput->Render()});
        });
    }

    ftxui::Component Naming::CreateComponentContainer()
    {
        return m_NameInput;
    }
}
