#pragma once
#include "../../../system/system.h"

namespace Aethereal
{
    namespace ECS::Systems::Core
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
