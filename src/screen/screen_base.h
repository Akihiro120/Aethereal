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
            Terminal::Print(1, 1, "Nothing to see here!!!");
        }

        virtual void Update()
        {
        }

    protected:
    };
}
