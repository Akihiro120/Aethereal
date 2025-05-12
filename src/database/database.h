#pragma once
#include <string>
#include <unordered_map>
#include "nlohmann.h"

using Json = nlohmann::json;

namespace Aethereal
{
    class Database
    {
    public:
        struct Entry
        {
            std::string path;
            Json data;
        };

        Database();

        void LoadFromDirectory(const std::string& path);
        Json* Get(const std::string& path);

    private:
        std::unordered_map<std::string, Entry> m_Database;
    };
}
