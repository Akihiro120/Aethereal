#include "screen_manager.h"
#include "../../terminal/terminal.h"

namespace Aethereal::Screen
{
    void ScreenManager::Replace(std::shared_ptr<ScreenBase> scr)
    {
        m_Screens.clear();
        m_Screens.push_back(scr);
    }

    void ScreenManager::Overlay(std::shared_ptr<ScreenBase> scr)
    {
        m_Screens.push_back(scr);
    }

    void ScreenManager::Pop()
    {
        m_Screens.pop_back();
    }

    void ScreenManager::Render()
    {
        if (m_Screens.empty())
        {
            Terminal::Print(0, 0, "No screen available for display!!!");
        }

        for (auto& screen : m_Screens)
        {
            screen->Render();
        }
    }

    void ScreenManager::Update()
    {
        if (!m_Screens.empty())
        {
            m_Screens.back()->Update();
        }
    }

}
