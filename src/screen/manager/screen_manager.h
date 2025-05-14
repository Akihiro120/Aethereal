#pragma once

// Aethereal
#include "../screen_base.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/loop.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <memory>
#include <vector>
#include "../../services/injector/injector.h"

namespace Aethereal::State
{
    class GameState;
}

namespace Aethereal::Screen
{

    class ScreenManager : Service::Injector<ScreenManager, State::GameState>
    {
    public:
        ScreenManager();
        void Replace(std::shared_ptr<ScreenBase> scr);
        void Overlay(std::shared_ptr<ScreenBase> scr);
        void Pop();

        void Render();
        bool IsClosed();
        void Clean();

    private:
        ftxui::Component CreateSceneRootComponent();
        std::vector<std::shared_ptr<ScreenBase>> m_Screens;

        ftxui::Component m_Container;
        ftxui::Component m_RootComponent;
        ftxui::Component m_SceneRootComponent;
        ftxui::ScreenInteractive m_InteractiveScreen;
        ftxui::Loop m_Loop;
    };
}
