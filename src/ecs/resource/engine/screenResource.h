#pragma once
#include <memory>
#include <vector>
#include "screen.h"

namespace Aethereal::ECS::Resource::Engine
{
    class ScreenResource
    {
    public:
        ScreenResource() = default;

        void Push(std::shared_ptr<IScreen> screen);
        void Pop();
        void Clear();

        void Create();
        void Step();
        void Draw();

    private:
        std::vector<std::shared_ptr<IScreen>> m_Screens;
    };
}
