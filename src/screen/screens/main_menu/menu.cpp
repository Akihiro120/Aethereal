#include "menu.h"
<<<<<<< HEAD
#include "naming.h"
=======
#include "raylib.h"
#include "raymath.h"
>>>>>>> parent of 4452e5f (did some stuff)

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
        }

        void Menu::Update()
        {
<<<<<<< HEAD
=======
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
                auto sm = GetInjection<ScreenManager>();

                if (m_Selection == 0)
                {
                }

                if (m_Selection == 1)
                {
                }

                if (m_Selection == 2)
                {
                }

                if (m_Selection == 3)
                {
                    GetInjection<State::GameState>()->StopRunning();
                }
            }
>>>>>>> parent of 4452e5f (did some stuff)
        }
    }
}
