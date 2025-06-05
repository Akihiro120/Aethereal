#include "world_system.h"
#include "../../database/nlohmann.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "../../utility/logging.h"

using Json = nlohmann::json;
namespace fs = std::filesystem;

namespace Aethereal::Systems
{

    WorldSystem::WorldSystem()
    {
    }

    WorldSystem::~WorldSystem()
    {
    }

    void WorldSystem::LoadAreas(const std::string& directory)
    {
        fs::path basePath = fs::path("../resources") / directory;

        if (!fs::exists(basePath))
        {
            Utility::Logging::LOG("Directory does not exist: " + basePath.string());
            return;
        }

        for (const auto& areaDir : fs::directory_iterator(basePath))
        {
            if (!areaDir.is_directory())
                continue;

            AreaData area;

            std::ifstream metafile(areaDir.path() / "area.json");
            Json metaJson;
            metafile >> metaJson;

            area.id = metaJson["id"];
            area.defaultZone = metaJson["defaultZone"];

            // Load each zone file
            Utility::Logging::LOG("Loaded Area: " + area.id);
            for (const auto& file : fs::directory_iterator(areaDir))
            {
                // we only want the zone, so filter out the area file.
                if (file.path().filename() == "area.json")
                {
                    continue;
                }

                std::ifstream zoneFile(file.path());
                Json zoneJson;
                zoneFile >> zoneJson;

                ZoneData zone;
                zone.id = zoneJson["id"];
                zone.description = zoneJson["description"];

                Utility::Logging::LOG("Loaded Zone: " + zone.id);
                for (const auto& [key, val] : zoneJson["exits"].items())
                {
                    Enums::Direction dir;
                    if (key == "north")
                        dir = Enums::Direction::NORTH;
                    else if (key == "south")
                        dir = Enums::Direction::SOUTH;
                    else if (key == "west")
                        dir = Enums::Direction::WEST;
                    else if (key == "east")
                        dir = Enums::Direction::EAST;

                    zone.exits[dir] = val;
                }

                area.zones[zone.id] = std::move(zone);
            }

            m_Areas[area.id] = std::move(area);
        }
    }

    void WorldSystem::Navigate(const Enums::Direction& dir)
    {
    }

    const std::string WorldSystem::CurrentAreaName()
    {
    }

    const std::string WorldSystem::CurrentAreaDescription()
    {
    }

    AreaZoneRef WorldSystem::ParseArea(const std::string& input, const std::string& currentArea)
    {
        size_t dot = input.find('.');
        if (dot == std::string::npos)
        {
            return {currentArea, input};
        }

        return {
            input.substr(0, dot),
            input.substr(dot + 1),
        };
    }
}
