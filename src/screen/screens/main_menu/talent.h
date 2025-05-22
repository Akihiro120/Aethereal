#pragma once
#include "../../screen_base.h"
#include <fecs/fecs.h>
#include "../../../services/injector/injector.h"
#include "../../../components/tags/player_component.h"
#include "../../../database/database.h"

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

        virtual void Render() override;
        virtual void Update() override;

    private:
        int RenderSelectionPanel(int offset);
        int RenderSpecification(int offset);
        int RenderStrengths(int offset);
        int RenderWeaknesses(int offset);
        int RenderFlavor(int offset);

        std::shared_ptr<Aethereal::Screen::ScreenManager> m_ScreenManager;
        std::shared_ptr<Database> m_Database;
        std::shared_ptr<FECS::Registry> m_Registry;

        FECS::View<Components::Tags::PlayerComponent> m_PlayerView;

        int m_Selected = 0;
        Json m_TalentList;
    };
}
