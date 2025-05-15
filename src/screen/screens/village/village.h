#pragma once
#include "../../screen_base.h"
#include "../../../services/injector/injector.h"
#include <fecs/fecs.h>

namespace Aethereal::Screen
{
    class ScreenManager;
}

namespace Aethereal::Screen
{
    class Village : public ScreenBase,
                    Service::Injector<Village, ScreenManager, FECS::Registry>
    {
    public:
        Village();

        virtual ftxui::Component CreateComponentRoot() override;
        virtual ftxui::Component CreateComponentContainer() override;

    private:
        std::shared_ptr<FECS::Registry> m_Registry;
        std::shared_ptr<ScreenManager> m_ScreenManager;

        ftxui::Component m_VillageOptionMenu;
        ftxui::Component m_InspectMenu;
        ftxui::Component m_VillageArmorMenu;
        ftxui::Component m_VillageWeaponMenu;

        ftxui::Component m_TabWindow;

        int m_Selection = 0;
        int m_Tab = 0;
        std::vector<std::string> m_VillageOptions;
    };
}
