#include "naming.h"
<<<<<<< HEAD
#include "../../../input/input_handler.h"
#include "../../../components/character/name_component.h"
#include "../../../components/tags/player_component.h"
#include "species.h"
=======
>>>>>>> parent of 4452e5f (did some stuff)

namespace Aethereal::Screen::MainMenu
{
    Naming::Naming()
    {
    }

    void Naming::Render()
    {
<<<<<<< HEAD
=======
        Terminal::Print(0, 0, "Name your Character");

        for (int i = 0; i < 16; i++)
        {
            // TODO: Move the unicode into enum for organisation
            Terminal::Put(i, 1, 0x2500);
        }
>>>>>>> parent of 4452e5f (did some stuff)
    }

    void Naming::Update()
    {
    }
}
