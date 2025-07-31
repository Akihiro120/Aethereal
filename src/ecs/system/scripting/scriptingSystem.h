#pragma once
#include "../core/system.h"

namespace Aethereal::ECS::Systems::Scripting
{
    class ScriptingSystem : public Core::ISystem
    {
    public:
        ScriptingSystem() = default;

        virtual void Create() override;

    private:
        void CreateLuaJITCompiler();
    };
}
