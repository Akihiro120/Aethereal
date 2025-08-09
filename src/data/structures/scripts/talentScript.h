#pragma once
#include <string>

namespace Aethereal::Data::Structures::Scripts
{
    struct TalentScript
    {
        std::string id;
        std::string name;
        std::string description;
        int difficulty;
    };
}
