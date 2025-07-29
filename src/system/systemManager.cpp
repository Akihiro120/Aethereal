#include "systemManager.h"

namespace Aethereal::Core
{
    void SystemManager::Create()
    {
        for (auto& [type, system] : m_Systems)
        {
            system->Create();
        }
    }

    void SystemManager::Step()
    {
        for (auto& [type, system] : m_Systems)
        {
            system->Step();
        }
    }

    void SystemManager::Draw()
    {
        for (auto& [type, system] : m_Systems)
        {
            system->Draw();
        }
    }

    void SystemManager::CleanUp()
    {
        for (auto& [type, system] : m_Systems)
        {
            system->CleanUp();
        }
    }

}
