#include "screen_manager.h"

namespace Aethereal::Screen
{
    ScreenManager::ScreenManager()
    {
    }

    void ScreenManager::Render()
    {
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

    void ScreenManager::Replace(std::shared_ptr<ScreenBase> scr)
    {
        Pop();
        m_Screens.push_back(scr);
    }

    void ScreenManager::Overlay(std::shared_ptr<ScreenBase> scr)
    {
        m_Screens.push_back(scr);
    }

    void ScreenManager::Pop()
    {
        if (!m_Screens.empty())
        {
            m_Screens.pop_back();
        }
    }

    void ScreenManager::Clean()
    {
        m_Screens.clear();
    }
}
