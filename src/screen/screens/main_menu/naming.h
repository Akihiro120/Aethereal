#pragma once
#include "../../screen_base.h"
#include "../../../services/injector/injector.h"
#include "../../manager/screen_manager.h"

namespace Aethereal::Screen
{
    namespace MainMenu
    {
        class Naming : public ScreenBase,
                       public Service::Injector<Naming, ScreenManager>
        {
        public:
            Naming();

            virtual void Render() override;
            virtual void Update() override;
        };
    }
}
