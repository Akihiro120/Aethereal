#include "naming.h"
#include "../../../input/input_handler.h"
#include "raylib.h"

#include "../../../components/character/name_component.h"
#include "../../../components/tags/player_component.h"
#include "species.h"

namespace Aethereal::Screen::MainMenu
{
    Naming::Naming()
        : m_Name("")
    {
    }

    void Naming::Render()
    {
        Terminal::SetForegroundColor(WHITE);
        Terminal::Print(0, 0, "Name your Character");

        for (int i = 0; i < 16; i++)
        {
            // TODO: Move the unicode into enum for organisation
            Terminal::Put(i, 1, 0x2500);
        }

        Terminal::SetForegroundColor(WHITE);
        if (m_Name.empty())
        {
            Terminal::SetForegroundColor(GRAY);
            Terminal::Print(0, 2, "Enter name...");
        }
        else
        {
            Terminal::Print(0, 2, m_Name);
        }
    }

    void Naming::Update()
    {
        Input::GetKeyboardInput(&m_Name);

        if (IsKeyPressed(KEY_ENTER) && !m_Name.empty())
        {
            // Create player and provide name
            auto ecs = GetInjection<FECS::Registry>();
            auto id = ecs->CreateEntity();
            ecs->Attach<Components::Tags::PlayerComponent>(id, {});
            ecs->Attach<Components::Character::NameComponent>(id, {m_Name});

            GetInjection<ScreenManager>()->Replace(std::make_shared<Species>());
        }
    }
}
