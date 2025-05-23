#pragma once
#include <string>
#include <unordered_map>
#include "../../data/enums/direction.h"

namespace Aethereal::Systems
{
    struct ZoneData
    {
        std::string id;
        std::string description;
        std::unordered_map<Enums::Direction, std::string> exits;
    };

    struct AreaData
    {
        std::string id;
        std::string defaultZone;
        std::unordered_map<Enums::Direction, ZoneData> zones;
    };

    class WorldSystem
    {
    public:
        WorldSystem();
        ~WorldSystem();

        void LoadAreas(const std::string& directory);
        void Navigate(const Enums::Direction& dir);
        const std::string CurrentAreaName();
        const std::string CurrentAreaDescription();

    private:
        std::unordered_map<std::string, AreaData> m_Areas;
    };
}
