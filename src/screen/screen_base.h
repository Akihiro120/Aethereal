#pragma once
#include "screen_interface.h"

namespace Aethereal::Screen
{
    class ScreenBase : public IScreen
    {
    public:
        ScreenBase()
        {
        }

        ~ScreenBase() = default;

        virtual void Render()
        {
        }

        virtual void Update()
        {
        }

    protected:
    };
}
