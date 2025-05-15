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
            .on_enter = [&] {}};
        m_VillageOptionMenu = Menu(&m_VillageOptions, &m_Selection, villageMenuOptions);

        auto root = Renderer([&]
        {
            return hbox({
                window(text(""), vbox({text("Village") | bold | hcenter,
                                       separator(),
                                       m_VillageOptionMenu->Render()})) |
                    size(WIDTH, EQUAL, 20),
            });
        });

        root |= CatchEvent([&](Event event)
        {
            if (Event::Character('q') == event)
            {
                return true;
            }
            return false;
        });

        return root;
    }

    ftxui::Component Village::CreateComponentContainer()
    {
        return Container::Vertical({m_VillageOptionMenu});
    }
}
