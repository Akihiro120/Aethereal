#include "game.h"

// Aethereal
#include "../services/service_locator/service_locator.h"
#include "../screen/manager/screen_manager.h"
#include "../terminal/terminal.h"
#include "../screen/screens/main_menu/menu.h"
#include "state/game_state.h"
#include <raylib.h>
#include <fecs/fecs.h>

namespace Aethereal
{
    using namespace Aethereal::Screen;
    using namespace Aethereal::Service;
    using namespace Aethereal::State;

    Aethereal::Aethereal()
    {
        // Prepare and setup services
        ServiceLocator::RegisterService(std::make_shared<GameState>());
        ServiceLocator::RegisterService(std::make_shared<ScreenManager>());
        ServiceLocator::RegisterService(std::make_shared<FECS::Registry>());

        // Setup Terminal
        TerminalCreateInfo info;
        info.width = 160;
        info.height = 50;
        info.fontSize = 18;
        info.fontPath = "../resources/font/FixedsysEx.ttf";
        info.title = "Aethereal";
        Terminal::Open(info);

        // set the first screen
        ServiceLocator::Get<ScreenManager>()->Overlay(std::make_shared<MainMenu::Menu>());
    }

    Aethereal::~Aethereal()
    {
        // Clean up and free resources.
        Clean();
    }

    void Aethereal::Run()
    {
        // Render loop.
        while (Terminal::IsWindowOpen() && ServiceLocator::Get<GameState>()->IsGameRunning())
        {
            // Progress the game's lifecycle.
            Update();

            // Render and display components to screen.
            Render();
        }
    }

    void Aethereal::Render()
    {
        Terminal::Clear();
        ServiceLocator::Get<ScreenManager>()->Render();

        Terminal::Refresh();
    }

    void Aethereal::Update()
    {
        ServiceLocator::Get<ScreenManager>()->Update();
    }

    void Aethereal::Clean()
    {
        Terminal::Close();
    }
}
