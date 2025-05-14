#include "screen_manager.h"
#include "../screens/empty.h"
#include <ftxui/component/component.hpp>
#include "../../game/state/game_state.h"

namespace Aethereal::Screen
{
    ScreenManager::ScreenManager() : m_InteractiveScreen(ftxui::ScreenInteractive::Fullscreen()),
                                     m_SceneRootComponent(CreateSceneRootComponent()),
                                     m_Container(ftxui::Container::Vertical({})),
                                     m_Loop(&m_InteractiveScreen, m_SceneRootComponent)
    {
        // Hide the cursor
        m_InteractiveScreen.SetCursor(ftxui::Screen::Cursor{0, 0, ftxui::Screen::Cursor::Shape::Hidden});

        Replace(std::make_shared<Empty>());
    }

    ftxui::Component ScreenManager::CreateSceneRootComponent()
    {
        using namespace ftxui;

        ftxui::Component component = ftxui::Renderer(m_Container, [this]
        {
            return m_RootComponent->Render();
        });

        component |= CatchEvent([&](Event event)
        {
            // Event handling for the screen
            m_RootComponent->OnEvent(event);

            // exit
            if (event == Event::Character('q'))
            {
                GetInjection<Aethereal::State::GameState>()->StopRunning();
            }

            return false;
        });

        return component;
    }

    void ScreenManager::Render()
    {
        m_Loop.RunOnce();
    }

    void ScreenManager::Replace(std::shared_ptr<ScreenBase> scr)
    {
        for (int i = 1; i < m_Screens.size(); i++)
        {
            m_Screens.pop_back();
        }

        m_Screens.push_back(scr);
        m_RootComponent = m_Screens.back()->GetComponentRoot();
        m_Container->DetachAllChildren();
        m_Container->Add(m_Screens.back()->GetComponentContainer());

        // m_SceneRootComponent = CreateSceneRootComponent();
    }

    bool ScreenManager::IsClosed()
    {
        return m_Loop.HasQuitted();
    }

    void ScreenManager::Overlay(std::shared_ptr<ScreenBase> scr)
    {
        m_Screens.push_back(scr);
    }

    void ScreenManager::Pop()
    {
        m_Screens.pop_back();
    }

    void ScreenManager::Clean()
    {
        m_Screens.clear();

        m_InteractiveScreen.Exit();
        m_InteractiveScreen.ExitLoopClosure();

        // NOTE: FAILSAFE for exiting ftxui
        std::cout << "\033[?25h\033[0m\033c" << std::flush;
    }
}
