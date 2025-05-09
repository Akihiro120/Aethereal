#include "menu.h"

namespace Aethereal::Screen
{
namespace MainMenu
{
Menu::Menu() : ScreenBase(CreateSceneRoot())
{
}

Menu::~Menu()
{
}

Component Menu::CreateSceneRoot()
{
    Component root;

    // Define the Menu Options
    m_Options = {"New Game", "Continue", "Exit"};

    m_OptionMenu = Menu(&m_Options, &m_OptionMenuSelection);

    // Define the menu
    root = Renderer(m_OptionMenu,
                    [&]
                    {
                        return vbox({text("Aethereal"), m_OptionMenu->Render()});
                    });

    return root;
}
} // namespace MainMenu
} // namespace Aethereal::Screen
