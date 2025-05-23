#include "navigation.h"
#include "../../manager/screen_manager.h"

namespace Aethereal::Screen
{
    Navigation::Navigation() : m_ScreenManager(GetInjection<ScreenManager>()),
                               m_Registry(GetInjection<FECS::Registry>()),
                               m_NavigationOptions({"North", "South", "East", "West"})
    {
    }

    void Navigation::Render()
    {
        Terminal::SetForegroundColor(WHITE);

        // Print boxes
        Terminal::DrawBox(0, 0, 20, Terminal::Height(), Terminal::BoxStyle::LIGHT);
        Terminal::DrawBox(21, 0, Terminal::Height() * 2, Terminal::Height(), Terminal::BoxStyle::LIGHT);
        Terminal::DrawBox(22 + Terminal::Height() * 2, 0, Terminal::Width() - 22 - Terminal::Height() * 2, Terminal::Height(), Terminal::BoxStyle::LIGHT);

        // Print labels
        Terminal::Print(1, 0, "Actions");
        Terminal::Print(22, 0, "Map");
        Terminal::Print(23 + Terminal::Height() * 2, 0, "Log");
    }

    void Navigation::Update()
    {
    }
}
