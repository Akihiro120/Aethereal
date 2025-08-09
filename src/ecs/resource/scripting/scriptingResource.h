#pragma once
#include <memory>
#include <string>
#include <sol/sol.hpp>
#include "../../../data/structures/scripts/talentScript.h"
#include "../../../data/structures/scripts/speciesScript.h"
#include "../../../data/structures/scripts/weaponScript.h"

using namespace Aethereal::Data::Structures::Scripts;

namespace Aethereal::ECS::Resource::Scripting
{

    // LuaEntity /////////////////////////////////////////////////////////////////////////////////////
    class LuaEntity
    {
    public:
        LuaEntity() = default;
    };

    // SCRIPTING SYSTEM //////////////////////////////////////////////////////////////////////////////

    class ScriptingResource
    {
    public:
        ScriptingResource();

        WeaponScript& GetWeaponScript(const std::string& id);

    private:
        void CreateLuaJITCompiler();
        void LoadWeapons();

    private:
        std::string m_FileRoot;
        std::unique_ptr<sol::state> m_LuaState;

        std::unordered_map<std::string, WeaponScript> m_WeaponScripts;
    };

    using ScriptingResourcePtr = std::shared_ptr<ScriptingResource>;
}
