#include "navigation.h"
#include "../../manager/screen_manager.h"

namespace Aethereal::Screen
{
    Navigation::Navigation() : m_ScreenManager(GetInjection<ScreenManager>()),
                               m_Registry(GetInjection<FECS::Registry>()),
                               m_NavigationOptions({"North", "South", "East", "West"})
    {
    }

}
