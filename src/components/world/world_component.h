#pragma once
#include <string>
#include <unordered_map>

namespace Aethereal::Components::World
{
    struct ZoneComponent
    {
        std::string id;
        std::string description;
        std::unordered_map<std::string, std::string> exits;
    };

    struct AreaComponent
    {
        std::string areaID;
    };

    struct CoordinateComponent
    {
        std::string area;
        std::string zone;
    };
}
