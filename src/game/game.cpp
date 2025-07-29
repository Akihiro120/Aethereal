#include "game.h"
#include <raylib.h>
#include "../ecs/system/core/engineSystem.h"

namespace Aethereal
{
    Game::Game()
    {
        m_SystemManager
            .AttachSystem<ECS::Systems::Core::EngineSystem>();
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

        m_SystemManager.Draw();

        EndDrawing();
    }

    void Game::CleanUp()
    {
        m_SystemManager.CleanUp();
    }
}
