#include "talent.h"
#include "confirm.h"
#include "../../../screen/manager/screen_manager.h"
#include "../../../database/database.h"
#include "../../../components/character/talent_component.h"

namespace Aethereal::Screen::MainMenu
{
    Talent::Talent()
        : m_ScreenManager(GetInjection<Aethereal::Screen::ScreenManager>()),
          m_Database(GetInjection<Database>()),
          m_Registry(GetInjection<FECS::Registry>()),
          m_PlayerView(m_Registry->View<Components::Tags::PlayerComponent>())
    {
    }
}
