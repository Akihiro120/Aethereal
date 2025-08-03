#pragma once
#include "../core/system.h"

namespace Aethereal
{
    namespace ECS::Systems::Engine
    {
        class EngineSystem : public Aethereal::Core::ISystem
        {
        public:
            EngineSystem() = default;

            virtual void Create() override;
            virtual void CleanUp() override;
        };
    }
}
