#include "navigation.h"
#include "../../manager/screen_manager.h"
#include <ftxui/component/component.hpp>

namespace Aethereal::Screen
{
    Navigation::Navigation() : m_ScreenManager(GetInjection<ScreenManager>()),
                               m_Registry(GetInjection<FECS::Registry>()),
                               m_NavigationOptions({"North", "South", "East", "West"})
    {
        ConstructSceneRoot();
    }

    using namespace ftxui;

    ftxui::Component Navigation::CreateComponentRoot()
    {
        auto villageMenuOptions = MenuOption{
            .on_enter = [&] {}};
        m_NavigationOptionMenu = Menu(&m_NavigationOptions, &m_Selection, villageMenuOptions);

        auto root = Renderer([&]
        {
            return hbox({
                window(text(""), vbox({text("Navigation") | bold | hcenter,
                                       separator(),
                                       m_NavigationOptionMenu->Render()})) |
                    size(WIDTH, EQUAL, 20),
            });
        });

        root |= CatchEvent([&](Event event)
        {
            return false;
        });

        return root;
    }

    ftxui::Component Navigation::CreateComponentContainer()
    {
        return Container::Vertical({m_NavigationOptionMenu});
    }
}
