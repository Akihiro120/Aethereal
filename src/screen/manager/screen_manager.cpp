#include "screen_manager.h"

namespace Aethereal::Screen
{
    Component ScreenManager::GetRootComponent()
    {
        // Display an empty msg if no screens are active
        if (m_Screens.empty())
        {
            return Renderer([&]
            {
                return text("Nothing to see here...");
            });
        }

        return Renderer(m_Screens.back()->GetComponent(), [&]
        {
            return m_Screens.back()->GetComponent()->Render();
        });
    }
}
