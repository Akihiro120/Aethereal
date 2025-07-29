#pragma once
#include <memory>
#include <unordered_map>
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
            std::type_index type(typeid(T));

            if (m_Systems.contains(type))
            {
                return *this;
            }

            m_Systems[type] = std::make_unique<T>();

            return *this;
        }

    private:
        std::unordered_map<std::type_index, std::unique_ptr<ISystem>> m_Systems;
    };
}
