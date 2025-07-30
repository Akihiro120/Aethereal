#pragma once
#include <memory>
#include <vector>
#include <typeindex>
#include "system.h"

namespace Aethereal::Core
{
    class SystemManager
    {
    public:
        SystemManager() = default;

        // Process
        void Create();
        void Step();
        void Draw();
        void CleanUp();

        // Management
        template <typename T>
        SystemManager& AttachSystem()
        {
            m_Systems.push_back(std::make_unique<T>());

            return *this;
        }

    private:
        std::vector<std::unique_ptr<ISystem>> m_Systems;
    };
}
