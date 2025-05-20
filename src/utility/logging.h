#pragma once
#include <cstdlib>
#include <iostream>

namespace Aethereal::Utility::Logging
{
    [[noreturn]] inline void ERROR(const char* msg)
    {
        std::cerr << "\x1B[31m" << msg << "\x1B[0m"
                  << std::endl;
        std::exit(EXIT_FAILURE);
    }

    [[noreturn]] inline void ERROR(const std::string& msg)
    {
        std::cerr << "\x1B[31m" << msg << "\x1B[0m"
                  << std::endl;
        std::exit(EXIT_FAILURE);
    }

    inline void LOG(const std::string& msg)
    {
        std::cerr << "\x1B[33m" << msg << "\x1B[0m"
                  << std::endl;
    }
}
