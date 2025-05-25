#pragma once
#include <string>
#include <unordered_map>
#include "../../data/enums/direction.h"

namespace Aethereal::Systems
{
    using ZoneID = std::string;

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
        std::unordered_map<ZoneID, ZoneData> zones;
    };

    struct AreaZoneRef
    {
        std::string area;
        std::string zone;
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
        AreaZoneRef ParseArea(const std::string& input, const std::string& currentArea);

        std::string m_CurrentArea = "";
        std::unordered_map<std::string, AreaData> m_Areas;
    };
}
