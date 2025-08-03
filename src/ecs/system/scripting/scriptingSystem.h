#pragma once
#include <string>
#include "../core/system.h"

namespace Aethereal::ECS::Systems::Scripting
{
    class ScriptingSystem : public Aethereal::Core::ISystem
    {
    public:
        ScriptingSystem() = default;

        virtual void Create() override;
    };
}
