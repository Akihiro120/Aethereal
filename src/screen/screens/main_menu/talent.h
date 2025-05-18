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
    class Talent : public ScreenBase,
                   Service::Injector<Talent, ScreenManager, Database, FECS::Registry>
    {
    public:
        Talent();

        struct TalentSpecification
        {
            std::vector<std::string> names;
            std::vector<std::string> descriptions;
            std::vector<std::string> flavors;
            std::vector<int> difficulties;
        };

    private:
        std::shared_ptr<Aethereal::Screen::ScreenManager> m_ScreenManager;
        std::shared_ptr<Database> m_Database;
        std::shared_ptr<FECS::Registry> m_Registry;

        FECS::View<Components::Tags::PlayerComponent> m_PlayerView;

        int m_Selected = 0;
        TalentSpecification m_TalentSpecification;
    };
}
