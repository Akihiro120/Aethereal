#include "game.h"
#include <raylib.h>
#include "../ecs/system/engine/engineSystem.h"
#include "../ecs/system/rendering/renderSystem.h"
#include "../ecs/system/scripting/scriptingSystem.h"
#include "../ecs/ecs.h"
#include "../ecs/resource/scripting/scriptingResource.h"
#include "../terminal/terminal.h"

namespace Aethereal
{
    Game::Game()
    {
        // Systems
        m_SystemManager
            .AttachSystem<ECS::Systems::Engine::EngineSystem>()
            .AttachSystem<ECS::Systems::Scripting::ScriptingSystem>()
            .AttachSystem<ECS::Systems::Render::RenderSystem>();

        // Components
    }

    Game::~Game()
    {
    }

    void Game::Run()
    {
        Create();
        while (!WindowShouldClose())
        {
            Step();
            Draw();
        }
        CleanUp();
    }

    void Game::Create()
    {
        m_SystemManager.Create();
    }

    void Game::Step()
    {
        m_SystemManager.Step();
    }

    void Game::Draw()
    {
        BeginDrawing();
        ClearBackground(BLACK);

        auto scripts = *ECS::Registry.Ctx<ECS::Resource::Scripting::ScriptingResourcePtr>();
        auto terminal = ECS::Registry.Ctx<Terminal>();
        if (scripts)
        {
            ECS::Resource::Scripting::WeaponScript weapon = scripts->GetWeaponScript("eclipseEdge");

            terminal->Print(0, 0, weapon.information["name"]);
            terminal->Print(0, 1, weapon.information["description"]);
            terminal->Print(0, 2, weapon.information["rarity"]);
        }

        m_SystemManager.Draw();

        EndDrawing();
    }

    void Game::CleanUp()
    {
        m_SystemManager.CleanUp();
    }
}
