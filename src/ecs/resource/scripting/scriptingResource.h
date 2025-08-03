#pragma once
#include <memory>
#include <string>
#include <sol/sol.hpp>

namespace Aethereal::ECS::Resource::Scripting
{

    // LuaEntity /////////////////////////////////////////////////////////////////////////////////////
    class LuaEntity
    {
    public:
        LuaEntity() = default;
    };

    // SCRIPTING SYSTEM //////////////////////////////////////////////////////////////////////////////

    struct WeaponScript
    {
        sol::table information;
        sol::table stats;
        sol::table scalings;
        sol::function passive;
        sol::function inspect;
        sol::function onHit;
        sol::function onUse;
        sol::function onEquip;
        sol::function onDrop;
    };

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
