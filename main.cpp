#include <cstdlib>
#include <iostream>
#include "src/game/game.h"

int main()
{
    try
    {
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
