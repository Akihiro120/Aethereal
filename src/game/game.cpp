#include "game.h"

// Aethereal
#include "../services/service_locator/service_locator.h"
#include "../screen/manager/screen_manager.h"
#include "../screen/screens/main_menu/menu.h"
#include "state/game_state.h"
#include <fecs/fecs.h>
<<<<<<< HEAD
#include "../components/tags/player_component.h"
#include "../components/character/name_component.h"
#include "../database/database.h"
#include "../terminal/terminal.h"
=======
>>>>>>> parent of 4452e5f (did some stuff)

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
<<<<<<< HEAD

        // set the first screen
        ServiceLocator::Get<ScreenManager>()->Overlay(std::make_shared<MainMenu::Menu>());

        // Setup Database
        auto db = ServiceLocator::Get<Database>();
        db->LoadFromDirectory("json/");

        // TODO: Abstract this into its own file for clean-ish-ness

        // ecs setup
        // PERF: Use Reserve functionality in ECS
        auto ecs = ServiceLocator::Get<FECS::Registry>();
        // ecs->GetEntityManager().Reserve(1000);
        ecs->RegisterComponent<Tags::PlayerComponent>();
        ecs->RegisterComponent<Character::NameComponent>();

        // terminal
        Terminal::Open();
=======
        TerminalCreateInfo info;
        info.width = 160;
        info.height = 50;
        info.fontSize = 18;
        info.fontPath = "../resources/font/FixedsysEx.ttf";
        info.title = "Aethereal";
        Terminal::Open(info);

        // set the first screen
        ServiceLocator::Get<ScreenManager>()->Overlay(std::make_shared<MainMenu::Menu>());
>>>>>>> parent of 4452e5f (did some stuff)
    }

    Aethereal::~Aethereal()
    {
        // Clean up and free resources.
        Clean();
    }

    void Aethereal::Run()
    {
        // Render loop.
        while (ServiceLocator::Get<GameState>()->IsGameRunning())
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
        Terminal::Print(0, 0, "Hello, World!!!");
        Terminal::Refresh();
    }

    void Aethereal::Update()
    {
        Terminal::Poll();
        ServiceLocator::Get<ScreenManager>()->Update();
    }

    void Aethereal::Clean()
    {
        Terminal::Close();
    }
}
