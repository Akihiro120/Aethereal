#pragma once
#include "../../screen_base.h"
#include "../../../services/injector/injector.h"
#include <fecs/fecs.h>
#include "../../../systems/world/world_system.h"

namespace Aethereal::Screen
{
    class ScreenManager;
}

namespace Aethereal::Screen
{
    class Navigation : public ScreenBase,
                       Service::Injector<Navigation, ScreenManager, FECS::Registry>
    {
    public:
        Navigation();

        virtual void Render() override;
        virtual void Update() override;

    private:
        void RenderOptions();
        void RenderMaps();
        void RenderLogs();

        Systems::WorldSystem m_WorldSystem;

        std::shared_ptr<FECS::Registry> m_Registry;
        std::shared_ptr<ScreenManager> m_ScreenManager;

        std::vector<std::string> m_NavigationOptions;

        int m_Selection = 0;
    };
}
