#include "naming.h"
#include "../../../components/character/name_component.h"
#include "../../../components/tags/player_component.h"
#include "../../../input/input_handler.h"
#include "species.h"

namespace Aethereal::Screen::MainMenu
{
    Naming::Naming()
        : m_ScreenManager(GetInjection<ScreenManager>()),
          m_Registry(GetInjection<FECS::Registry>()),
          m_Name("")
    {
    }

    void Naming::Render()
    {
        Terminal::SetForegroundColor(WHITE);
        Terminal::DrawBox(0, 0, Terminal::Width(), Terminal::Height(), Terminal::BoxStyle::LIGHT);
        Terminal::Print(1, 0, "Name your Character");

        if (m_Name.empty())
        {
            Terminal::SetForegroundColor(GRAY);
            Terminal::Print(1, 1, "Enter your Name...");
        }
        else
        {
            Terminal::SetForegroundColor(WHITE);
            Terminal::Print(1, 1, m_Name + "|");
        }
    }

    void Naming::Update()
    {
        Aethereal::Input::GetKeyboardInput(&m_Name);

        if (IsKeyPressed(KEY_ENTER) && !m_Name.empty())
        {

            // Attach name component to player entity
            FECS::Entity player = m_Registry->CreateEntity();
            m_Registry->Attach(player, Components::Tags::PlayerComponent{});
            m_Registry->Attach(player, Components::Character::NameComponent{.name = m_Name});

            // Replace screen
            m_ScreenManager->Replace(std::make_shared<Species>());
        }
    }
}
