#include "renderSystem.h"
#include "../../../ecs/ecs.h"
#include "../../../terminal/terminal.h"

namespace Aethereal::ECS::Systems::Render
{
    void RenderSystem::Create()
    {
        FECS::Entity terminal = ECS::Registry.CreateEntity();
        Terminal& t = ECS::Registry.GetOrAttach<Terminal>(terminal, {});

        Terminal::Config config;
        config.fontPath = "resources/font/CascadiaCove.ttf";

        t.ToggleDPIScaling(false);
        t.Open(config);
    }

    void RenderSystem::Draw()
    {
        Terminal* terminal = ECS::Registry.Ctx<Terminal>();
        if (terminal)
        {
            terminal->Refresh();
        }
    }
    void RenderSystem::CleanUp()
    {
        Terminal* terminal = ECS::Registry.Ctx<Terminal>();
        if (terminal)
        {
            terminal->Close();
        }
    }
}
