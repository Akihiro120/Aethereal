#pragma once
#include "../core/system.h"

namespace Aethereal::ECS::Systems::Render
{
    class RenderSystem : public Aethereal::Core::ISystem
    {
    public:
        RenderSystem() = default;

        virtual void Create();
        virtual void Draw();
        virtual void CleanUp();
    };
}
