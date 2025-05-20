#include "game.h"

// Aethereal
#include "../services/service_locator/service_locator.h"
#include "../screen/manager/screen_manager.h"
#include "../screen/screens/main_menu/menu.h"
#include "state/game_state.h"
#include <fecs/fecs.h>
#include "../components/tags/player_component.h"
#include "../components/character/name_component.h"
#include "../database/database.h"
#include "../terminal/terminal.h"

namespace Aethereal
{
    using namespace Aethereal::Screen;
    using namespace Aethereal::Service;
    using namespace Aethereal::State;
    using namespace Aethereal::Components;

    Aethereal::Aethereal()
    {
        RegisterServices();
        InitializeECS();
        LoadDatabase();
        InitialTerminal();
        SetInitialScreen();
    }

    Aethereal::~Aethereal()
    {
        Clean();
    }

    void Aethereal::RegisterServices()
    {
        ServiceLocator::RegisterService(std::make_shared<GameState>());
        ServiceLocator::RegisterService(std::make_shared<ScreenManager>());
        ServiceLocator::RegisterService(std::make_shared<FECS::Registry>());
        ServiceLocator::RegisterService(std::make_shared<Database>());
    }

    void Aethereal::InitializeECS()
    {
        auto ecs = ServiceLocator::Get<FECS::Registry>();
        ecs->RegisterComponent<Tags::PlayerComponent>();
        ecs->RegisterComponent<Character::NameComponent>();
    }

    void Aethereal::LoadDatabase()
    {
        auto db = ServiceLocator::Get<Database>();
        db->LoadFromDirectory("json/");
    }

    void Aethereal::InitialTerminal()
    {
        Terminal::Open(Terminal::TerminalConfig{
            .windowWidth = 1280,
            .windowHeight = 720,
            .columns = 160,
            .rows = 50,
            .fontPath = "../resources/font/CascadiaCove.ttf",
        });
    }

    void Aethereal::SetInitialScreen()
    {
        auto sm = ServiceLocator::Get<ScreenManager>();
        sm->Replace(std::make_shared<MainMenu::Menu>());
    }

    void Aethereal::Run()
    {
        // Render loop.
        while (ServiceLocator::Get<GameState>()->IsGameRunning() && !WindowShouldClose())
        {
            Update();
            Render();
        }
    }

    void Aethereal::Render()
    {
        auto sm = ServiceLocator::Get<ScreenManager>();

        Terminal::Clear();
        sm->Render();
        Terminal::Refresh();
    }

    void Aethereal::Update()
    {
        auto sm = ServiceLocator::Get<ScreenManager>();
        sm->Update();
    }

    void Aethereal::Clean()
    {
        ServiceLocator::Get<ScreenManager>()->Clean();
        ServiceLocator::Clean();
        Terminal::Close();
    }
}
