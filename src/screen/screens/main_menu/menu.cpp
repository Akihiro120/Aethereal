#include "menu.h"
#include "raylib.h"
#include "raymath.h"

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
            Terminal::Print(0, 0, "Aethereal - Development Edition");

            for (int i = 0; i < 16; i++)
            {
                // TODO: Move the unicode into enum for organisation
                Terminal::Put(i, 1, 0x2500);
            }

            for (int i = 0; i < m_Options.size(); i++)
            {
                const std::string& opt = m_Options[i];
                Terminal::SetForegroundColor(WHITE);
                int offset = 0;
                if (m_Selection == i)
                {
                    offset = 2;
                    Terminal::SetForegroundColor(YELLOW);
                    Terminal::Put(0, 2 + i, '>');
                }
                Terminal::Print(offset, 2 + i, opt);
            }
        }

        void Menu::Update()
        {
            if (IsKeyPressed(KEY_K) || IsKeyPressed(KEY_UP))
            {
                m_Selection--;
                m_Selection = Clamp(m_Selection, 0, m_Options.size() - 1);
            }

            if (IsKeyPressed(KEY_J) || IsKeyPressed(KEY_DOWN))
            {
                m_Selection++;
                m_Selection = m_Selection % (m_Options.size());
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                // Goto next screen
                auto sm = Get<ScreenManager>();

                if (m_Selection == 3)
                {
                    CloseWindow();
                }
            }
        }
    }
}
