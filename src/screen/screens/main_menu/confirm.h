#pragma once
#include "../../screen_base.h"
#include "../../../services/injector/injector.h"
#include <fecs/fecs.h>

namespace Aethereal::Screen
{
    class ScreenManager;
}

namespace Aethereal::Screen::MainMenu
{

    class Confirm : public ScreenBase,
                    Service::Injector<Confirm, FECS::Registry, ScreenManager>
    {
    public:
        Confirm();

    private:
        std::shared_ptr<FECS::Registry> m_Registry;
        std::shared_ptr<Aethereal::Screen::ScreenManager> m_ScreenManager;
        FECS::Entity m_PlayerID;
    };
}
