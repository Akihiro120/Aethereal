#include "scriptingSystem.h"
#include "../../resource/scripting/scriptingResource.h"
#include "../../../ecs/ecs.h"

namespace Aethereal::ECS::Systems::Scripting
{
    using namespace Resource::Scripting;

    void ScriptingSystem::Create()
    {
        // Create scripting resource
        FECS::Entity scriptResource = ECS::Registry.CreateEntity();

        ScriptingResourcePtr scriptRes = std::make_shared<ScriptingResource>();
        ECS::Registry.Attach<ScriptingResourcePtr>(scriptResource, scriptRes);
    }
}
