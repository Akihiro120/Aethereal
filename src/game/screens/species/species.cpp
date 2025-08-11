#include "species.h"
#include "../../../ecs/ecs.h"
#include "../../../terminal/terminal.h"

namespace Aethereal::Screens
{
    void Species::Create()
    {
    }

    void Species::Step()
    {
    }

    void Species::Draw()
    {
        Terminal* terminal = ECS::Registry.Ctx<Terminal>();
        terminal->SetForegroundColor(WHITE);

        terminal->Print(0, 0, "Select your Species");
    }
}
