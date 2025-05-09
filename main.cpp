#include <cstdlib>
#include <iostream>
#include "src/game/game.h"

#include "src/screen/manager/screen_manager.h"
#include "src/services/service_locator/service_locator.h"

using namespace Aethereal::Screen;
using namespace Aethereal::Service;

int main()
{
    try
    {
        // Prepare and setup services
        ServiceLocator::RegisterService(std::make_shared<ScreenManager>());

        // Begin the game
        Aethereal::Aethereal aethereal;
        aethereal.Run();
    }
    catch (const std::exception& e)
    {
        // Fail
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
