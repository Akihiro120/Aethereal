#pragma once
#include "../core/system.h"

namespace Aethereal::ECS::System::Engine
{
    class SaveSystem : public Core::ISystem
    {
    public:
        SaveSystem() = default;

        virtual void Create() override;

    private:
        void LoadSettings();
    };
}
