#include "engineSystem.h"
#include <raylib.h>

namespace Aethereal::ECS::Systems::Core
{
    void EngineSystem::Create()
    {
        SetTraceLogLevel(TraceLogLevel::LOG_NONE);
        InitWindow(1280, 720, "Aethereal");
        SetTargetFPS(60);
    }

    void EngineSystem::CleanUp()
    {
        CloseWindow();
    }
}
