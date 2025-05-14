#include "game.h"

// Aethereal
#include "../services/service_locator/service_locator.h"
#include "../screen/manager/screen_manager.h"
#include "../screen/screens/main_menu/menu.h"
#include "state/game_state.h"
#include <fecs/fecs.h>
#include <chrono>
#include <thread>
#include "../components/tags/player_component.h"
#include "../components/character/name_component.h"
#include "../database/database.h"

namespace Aethereal
{
    using namespace Aethereal::Screen;
    using namespace Aethereal::Service;
    using namespace Aethereal::State;
    using namespace Aethereal::Components;

    Aethereal::Aethereal()
    {
        // Prepare and setup services
        ServiceLocator::RegisterService(std::make_shared<GameState>());
        ServiceLocator::RegisterService(std::make_shared<ScreenManager>());
        ServiceLocator::RegisterService(std::make_shared<FECS::Registry>());
        ServiceLocator::RegisterService(std::make_shared<Database>());

        // set the first screen
        auto sm = ServiceLocator::Get<ScreenManager>();
        sm->Replace(std::make_shared<MainMenu::Menu>());

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
    }

    Aethereal::~Aethereal()
    {
        // Clean up and free resources.
        Clean();
    }

    using namespace std::chrono;
    void Aethereal::Run()
    {
        auto frameTime = milliseconds(1000 / 60);

        // Render loop.
        while (ServiceLocator::Get<GameState>()->IsGameRunning() && !ServiceLocator::Get<ScreenManager>()->IsClosed())
        {
            // Progress the game's lifecycle.
            Update();

            // Render and display components to screen.
            Render();

            std::this_thread::sleep_for(frameTime);
        }
    }

    void Aethereal::Render()
    {
        auto sm = ServiceLocator::Get<ScreenManager>();
        sm->Render();
    }

    void Aethereal::Update()
    {
    }

    void Aethereal::Clean()
    {
        ServiceLocator::Get<ScreenManager>()->Clean();
        ServiceLocator::Clean();
    }
}
