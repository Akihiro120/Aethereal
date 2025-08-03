#include "engineSystem.h"
#include <raylib.h>
#include "../../../terminal/terminal.h"

namespace Aethereal::ECS::Systems::Engine
{
    void EngineSystem::Create()
    {
        SetTraceLogLevel(TraceLogLevel::LOG_NONE);
        InitWindow(1920, 1080, "Aethereal");
        SetTargetFPS(60);
    }

    void EngineSystem::CleanUp()
    {
        CloseWindow();
    }
}
