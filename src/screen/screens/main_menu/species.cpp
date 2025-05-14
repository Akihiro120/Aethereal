#include "species.h"

namespace Aethereal::Screen::MainMenu
{
    Species::Species() : m_ScreenManager(*GetInjection<ScreenManager>()),
                         m_ECS(*GetInjection<FECS::Registry>()),
                         m_Database(*GetInjection<Database>())

    {
    }

    ftxui::Component Species::CreateComponentRoot()
    {
    }
}
