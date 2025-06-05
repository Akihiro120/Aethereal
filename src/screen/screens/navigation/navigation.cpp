#include "navigation.h"
#include "../../manager/screen_manager.h"

namespace Aethereal::Screen
{
    Navigation::Navigation() : m_ScreenManager(GetInjection<ScreenManager>()),
                               m_Registry(GetInjection<FECS::Registry>()),
                               m_NavigationOptions({"North", "South", "East", "West"})
    {
        // load areas
        m_WorldSystem.LoadAreas("json/areas");
    }

    void Navigation::Render()
    {
        Terminal::SetForegroundColor(WHITE);

        int w = Terminal::Width();
        int h = Terminal::Height();

        // Print boxes
        Terminal::DrawBox(0, 0, 20, h, Terminal::BoxStyle::LIGHT);
        Terminal::DrawBox(21, 0, h * 2, h, Terminal::BoxStyle::LIGHT);
        Terminal::DrawBox(22 + h * 2, 0, w - 22 - h * 2, h, Terminal::BoxStyle::LIGHT);

        // Print labels
        Terminal::Print(1, 0, "Actions");
        Terminal::Print(22, 0, "Map");
        Terminal::Print(23 + h * 2, 0, "Log");

        RenderOptions();
        RenderMaps();
        RenderLogs();
    }

    void Navigation::RenderOptions()
    {
    }

    void Navigation::RenderMaps()
    {
    }

    void Navigation::RenderLogs()
    {
    }

    void Navigation::Update()
    {
    }
}
