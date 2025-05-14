#include <cstdlib>
#include <iostream>
#include "raylib.h"
#include "src/game/game.h"

int main()
{
    try
    {
        SetTraceLogLevel(7);

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
