#include "game.h"

// Aethereal
#include "../services/service_locator/service_locator.h"
#include "../screen/manager/screen_manager.h"
#include "../terminal/terminal.h"
#include "../screen/screens/main_menu/menu.h"

namespace Aethereal
{
    using namespace Aethereal::Screen;
    using namespace Aethereal::Service;

    Aethereal::Aethereal()
    {
        // Prepare and setup services
        ServiceLocator::RegisterService(std::make_shared<ScreenManager>());

        TerminalCreateInfo info;
        info.width = 160;
        info.height = 50;
        info.fontSize = 24;
        info.fontPath = "../resources/font/CascadiaCove.ttf";
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
        while (Terminal::IsWindowOpen())
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

        Terminal::SetForegroundColor(GRAY);
        Terminal::Print(0, Terminal::GetHeight() - 1, "FPS: " + std::to_string(GetFPS()));
        Terminal::SetForegroundColor(WHITE);
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
