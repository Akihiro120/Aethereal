#include "screenResource.h"
#include "../../../game/screens/mainMenu/mainMenu.h"

namespace Aethereal::ECS::Resource::Engine
{

    void ScreenResource::Push(std::shared_ptr<IScreen> screen)
    {
        m_Screens.push_back(std::move(screen));
    }

    void ScreenResource::Pop()
    {
        m_Screens.pop_back();
    }

    void ScreenResource::Clear()
    {
        m_Screens.clear();
    }

    void ScreenResource::Create()
    {
        m_Screens.push_back(std::make_shared<Screens::MainMenu>());

        for (auto& screen : m_Screens)
        {
            screen->Create();
        }
    }

    void ScreenResource::Step()
    {
        for (auto& screen : m_Screens)
        {
            screen->Step();
        }
    }

    void ScreenResource::Draw()
    {
        for (auto& screen : m_Screens)
        {
            screen->Draw();
        }
    }
}
