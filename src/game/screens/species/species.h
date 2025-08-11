#pragma once
#include "../../../ecs/resource/engine/screen.h"

namespace Aethereal::Screens
{
    class Species : public ECS::Resource::Engine::IScreen
    {
    public:
        Species() = default;

        virtual void Create() override;
        virtual void Step() override;
        virtual void Draw() override;
    };
}
