#include "database.h"
#include <filesystem>
#include <fstream>
#include "../utility/logging.h"

namespace Aethereal
{
    Database::Database()
    {
    }

    void Database::LoadFromDirectory(const std::string& path)
    {
        try
        {
            for (const auto& entry : std::filesystem::directory_iterator("../resources/" + path))
            {
                if (entry.is_regular_file() && entry.path().extension() == ".json")
                {
                    std::ifstream file(entry.path().string());
                    if (file)
                    {
                        Json data;
                        file >> data;
                        m_Database[entry.path().stem().string()].data = std::move(data);
                        m_Database[entry.path().stem().string()].path = entry.path().string();
                        Utility::Logging::LOG("Database::Loaded: " + entry.path().string());
                    }
                    else
                    {
                        Utility::Logging::ERROR("Database::LoadFromDirectory: " + entry.path().string());
                    }
                }
            }
        }
        catch (const std::exception& e)
        {
            Utility::Logging::ERROR(std::string("Database::LoadFromDirectory: ") + e.what());
        }
    }

    Json* Database::Get(const std::string& path)
    {
        auto it = m_Database.find(path);
        if (it != m_Database.end())
        {
            return &it->second.data;
        }
        else
        {
            Utility::Logging::ERROR("Database::Get: Invalid Path" + it->second.path);
            return nullptr;
        }
    }
}
