#include "mainMenu.h"
#include "../../../ecs/ecs.h"
#include "../../../terminal/terminal.h"

namespace Aethereal::Screens
{
    void MainMenu::Create()
    {
        m_Options = {
            "New Game",
            "Continue",
            "Exit Game",
        };
    }

    void MainMenu::Step()
    {
    }

    void MainMenu::Draw()
    {
        Terminal* terminal = ECS::Registry.Ctx<Terminal>();
        terminal->SetForegroundColor(WHITE);
        terminal->Print(0, 0, "Aethereal");

        for (int i = 0; i < m_Options.size(); i++)
        {
            Color highlight = WHITE;
            if (m_Selection == i)
            {
                highlight = YELLOW;
            }

            terminal->SetForegroundColor(highlight);
            terminal->Print(0, 1 + i, m_Options[i]);
        }
    }
}
