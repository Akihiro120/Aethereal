#pragma once
#include <string>
#include <vector>
#include "../../../ecs/resource/engine/screen.h"

namespace Aethereal::Screens
{
    class MainMenu : public ECS::Resource::Engine::IScreen
    {
    public:
        MainMenu() = default;

        virtual void Create() override;
        virtual void Step() override;
        virtual void Draw() override;

    private:
        unsigned int m_Selection = 0;
        std::vector<std::string> m_Options;
    };
}
