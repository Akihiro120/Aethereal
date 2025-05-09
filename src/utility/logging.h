#pragma once
#include <cstdlib>
#include <iostream>

namespace Aethereal::Utility
{
    [[noreturn]] inline void ERROR(const char* msg)
    {
        std::cerr << msg << std::endl;
        std::exit(EXIT_FAILURE);
    }

    [[noreturn]] inline void ERROR(const std::string& msg)
    {
        std::cerr << msg << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
