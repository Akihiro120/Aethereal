#pragma once
#include "../../screen_base.h"
#include "../../../services/injector/injector.h"
#include "../../manager/screen_manager.h"
#include <fecs/fecs.h>

namespace Aethereal::Screen
{
    namespace MainMenu
    {
        class Naming : public ScreenBase,
                       public Service::Injector<Naming, ScreenManager, FECS::Registry>
        {
        public:
            Naming();

            virtual ftxui::Component CreateComponentRoot() override;

        private:
            std::string m_Name;
        };
    }
}
