#include "scriptingResource.h"
#include <filesystem>
#include "../../ecs.h"

namespace Aethereal::ECS::Resource::Scripting
{
    // LuaEntity /////////////////////////////////////////////////////////////////////////////////////

    // SCRIPTING SYSTEM //////////////////////////////////////////////////////////////////////////////

    ScriptingResource::ScriptingResource()
        : m_FileRoot("resources/scripts/")
    {
        m_LuaState = std::make_unique<sol::state>();
        CreateLuaJITCompiler();
    }

    void ScriptingResource::CreateLuaJITCompiler()
    {
        m_LuaState->open_libraries(
            sol::lib::base,
            sol::lib::package,
            sol::lib::math,
            sol::lib::string);

        LoadWeapons();
    }

    void ScriptingResource::LoadWeapons()
    {
        namespace fs = std::filesystem;
        fs::path folder = fs::path(m_FileRoot) / "weapons";

        if (!fs::exists(folder) || !fs::is_directory(folder))
        {
            std::cerr << "Scripting Resource: folder not found: " << folder << std::endl;
            return;
        }

        for (auto& entry : fs::directory_iterator(folder))
        {
            if (entry.path().extension() != ".lua")
            {
                continue;
            }

            sol::table tbl;
            tbl = m_LuaState->script_file(entry.path().string());

            std::string id = tbl.get_or<std::string>("id", "");
            if (id.empty())
            {
                std::cerr << "Scripting Resource: script at " << entry.path() << " has no `id` field; skipping" << std::endl;
                continue;
            }

            WeaponScript script;
            script.id = tbl["id"];
            script.name = tbl["name"];
            script.description = tbl["description"];
            script.rarity = tbl["rarity"];
            m_WeaponScripts[id] = script;
        }
    }

    WeaponScript& ScriptingResource::GetWeaponScript(const std::string& id)
    {
        auto it = m_WeaponScripts.find(id);
        if (it == m_WeaponScripts.end())
        {
            std::cerr << "Scripting Resource: Weapon Script not found: " + id << std::endl;
        }

        return it->second;
    }
}
