#include "world_system.h"
#include "../../database/nlohmann.h"
#include <filesystem>
#include <fstream>
#include <iostream>

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
        for (const auto& areaDir : fs::directory_iterator(directory))
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

    void WorldSystem::ParseArea(const std::string& areaID)
    {
    }
}
