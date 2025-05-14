#pragma once
#include "../screen_base.h"

namespace Aethereal::Screen
{
    class Empty : public ScreenBase
    {
    public:
        Empty();

        virtual ftxui::Component CreateComponentRoot() override;
    };
}
