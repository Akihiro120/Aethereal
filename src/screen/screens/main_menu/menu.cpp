#include "menu.h"
#include "naming.h"
#include <raylib.h>
#include <raymath.h>

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
        }

        Menu::~Menu()
        {
        }

        void Menu::Render()
        {
            Terminal::SetForegroundColor(WHITE);
            Terminal::DrawBox(0, 0, Terminal::Width(), Terminal::Height(), Terminal::BoxStyle::LIGHT);
            Terminal::Print(1, 0, "Aethereal");

            for (int i = 0; i < m_Options.size(); i++)
            {
                Color optionColor = WHITE;
                std::string prefix = "";
                if (i == m_Selection)
                {
                    prefix = "> ";
                    optionColor = YELLOW;
                }
                Terminal::SetForegroundColor(optionColor);
                Terminal::Print(1, 1 + i, prefix + m_Options[i]);

                Terminal::SetForegroundColor(WHITE);
            }
        }

        void Menu::Update()
        {
            if (IsKeyPressed(KEY_K))
            {
                m_Selection = Clamp(m_Selection - 1, 0, m_Options.size() - 1);
            }

            if (IsKeyPressed(KEY_J))
            {
                m_Selection = Clamp(m_Selection + 1, 0, m_Options.size() - 1);
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                GetInjection<ScreenManager>()->Replace(std::make_shared<Naming>());
            }
        }
    }
}
