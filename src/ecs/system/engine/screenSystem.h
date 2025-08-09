#pragma once
#include "../core/system.h"

namespace Aethereal::ECS::Systems::Engine
{
    class ScreenSystem : public Core::ISystem
    {
    public:
        ScreenSystem() = default;

        virtual void Create() override;
        virtual void Step() override;
        virtual void Draw() override;

    private:
    };
}
