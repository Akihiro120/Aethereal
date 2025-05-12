#include "naming.h"

namespace Aethereal::Screen::MainMenu
{
    Naming::Naming()
    {
    }

    void Naming::Render()
    {
        Terminal::Print(0, 0, "Name your Character");

        for (int i = 0; i < 16; i++)
        {
            // TODO: Move the unicode into enum for organisation
            Terminal::Put(i, 1, 0x2500);
        }
    }

    void Naming::Update()
    {
    }
}
