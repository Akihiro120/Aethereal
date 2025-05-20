#pragma once
#include "../../screen_base.h"
#include <fecs/fecs.h>
#include "../../../services/injector/injector.h"
#include "../../../components/tags/player_component.h"

namespace Aethereal::Screen
{
    class ScreenManager;
}

namespace Aethereal
{
    class Database;
}

namespace Aethereal::Screen::MainMenu
{

    class Species : public ScreenBase,
                    public Service::Injector<Species, ScreenManager, FECS::Registry, Database>
    {
    public:
        Species();

        virtual void Render() override;
        virtual void Update() override;

    private:
        std::shared_ptr<ScreenManager> m_ScreenManager;
        std::shared_ptr<FECS::Registry> m_Registry;
        std::shared_ptr<Database> m_Database;

        int m_Selected = 0;
        FECS::View<Components::Tags::PlayerComponent> m_PlayerView;
    };
}
