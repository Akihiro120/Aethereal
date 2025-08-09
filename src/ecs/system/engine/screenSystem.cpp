#include "screenSystem.h"
#include "../../resource/engine/screenResource.h"
#include "../../ecs.h"

namespace Aethereal::ECS::Systems::Engine
{
    using namespace Resource::Engine;

    void ScreenSystem::Create()
    {
        FECS::Entity resource = ECS::Registry.CreateEntity();
        ECS::Registry.Attach<ScreenResource>(resource, {});

        ScreenResource* screenResource = ECS::Registry.Ctx<ScreenResource>();
        screenResource->Create();
    }

    void ScreenSystem::Step()
    {
        ScreenResource* screenResource = ECS::Registry.Ctx<ScreenResource>();
        screenResource->Step();
    }

    void ScreenSystem::Draw()
    {
        ScreenResource* screenResource = ECS::Registry.Ctx<ScreenResource>();
        screenResource->Draw();
    }

}
