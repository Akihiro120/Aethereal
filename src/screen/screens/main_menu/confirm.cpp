#include "confirm.h"
#include "../../manager/screen_manager.h"
#include "../../../components/tags/player_component.h"
#include "../../../components/character/name_component.h"
#include "../../../components/character/species_component.h"
#include "../../../components/character/talent_component.h"
#include "../navigation/navigation.h"

#include "../../../components/character/stats/general_stat_component.h"

namespace Aethereal::Screen::MainMenu
{
    Confirm::Confirm()
        : m_Registry(GetInjection<FECS::Registry>()),
          m_ScreenManager(GetInjection<Aethereal::Screen::ScreenManager>())
    {
    }
}
