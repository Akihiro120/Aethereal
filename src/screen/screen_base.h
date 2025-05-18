#pragma once
#include "screen_interface.h"
#include "../terminal/terminal.h"

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
            Terminal::Print(0, 0, "Not Yet Implemented");
        }

        virtual void Update()
        {
        }

    protected:
    };
}
