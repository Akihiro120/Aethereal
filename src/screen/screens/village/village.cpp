#include "village.h"
#include "../../manager/screen_manager.h"
#include <ftxui/component/component.hpp>

namespace Aethereal::Screen
{
    Village::Village() : m_ScreenManager(GetInjection<ScreenManager>()),
                         m_Registry(GetInjection<FECS::Registry>()),
                         m_VillageOptions({"Encounter",
                                           "Buy Armor",
                                           "Buy Weapons",
                                           "Inspect"})
    {
        ConstructSceneRoot();
    }

    using namespace ftxui;

    ftxui::Component Village::CreateComponentRoot()
    {
        auto villageMenuOptions = MenuOption{
            .on_enter = [&]
        {
            if (m_Selection == 0)
            {
                m_Tab = 1;
            }
            if (m_Selection == 1)
            {
                m_Tab = 2;
            }
            if (m_Selection == 2)
            {
                m_Tab = 3;
            }
            if (m_Selection == 3)
            {
                m_Tab = 4;
            }
        }};
        m_VillageOptionMenu = Menu(&m_VillageOptions, &m_Selection, villageMenuOptions);

        m_VillageArmorMenu = Renderer([&]
        {
            return text("Armor Menu");
        });
        m_VillageWeaponMenu = Renderer([&]
        {
            return text("Weapon Menu");
        });
        m_InspectMenu = Renderer([&]
        {
            return text("Inspect Menu");
        });

        m_TabWindow = Container::Tab({m_VillageArmorMenu, m_VillageWeaponMenu, m_InspectMenu}, &m_Tab);

        auto root = Renderer([&]
        {
            return hbox({window(text(""), vbox({text("Village") | bold | hcenter,
                                                separator(),
                                                m_VillageOptionMenu->Render()})) |
                             size(WIDTH, EQUAL, 20),
                         window(text(""), m_TabWindow->Render())});
        });

        root |= CatchEvent([&](Event event)
        {
            if (Event::Character('q') == event)
            {
                m_Tab = 0;
                return true;
            }
            return false;
        });

        return root;
    }

    ftxui::Component Village::CreateComponentContainer()
    {
        return Container::Tab({m_VillageArmorMenu, m_VillageWeaponMenu, m_InspectMenu}, &m_Tab);
    }
}
