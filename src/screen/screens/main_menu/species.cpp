#include "species.h"
#include "../../manager/screen_manager.h"
#include "../../../database/database.h"
#include "../../../components/character/species_component.h"
#include "talent.h"

namespace Aethereal::Screen::MainMenu
{
    Species::Species() : m_ScreenManager(GetInjection<ScreenManager>()),
                         m_Registry(GetInjection<FECS::Registry>()),
                         m_Database(GetInjection<Database>()),
                         m_PlayerView(m_Registry->View<Components::Tags::PlayerComponent>())

    {
    }

}
