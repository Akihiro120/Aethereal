#pragma once
#include <string>

namespace Aethereal::Data::Structures::Scripts
{
    struct SpeciesScript
    {
        std::string id;
        std::string name;
        std::string description;
        std::string origin;
        int difficulty;
    };
}
