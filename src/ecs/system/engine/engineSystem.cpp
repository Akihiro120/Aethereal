#include "engineSystem.h"
#include <raylib.h>

namespace Aethereal::ECS::Systems::Engine
{
    void EngineSystem::Create()
    {
        SetTraceLogLevel(TraceLogLevel::LOG_NONE);
        SetConfigFlags(FLAG_WINDOW_HIGHDPI);
        InitWindow(1280, 720, "Aethereal");
        SetTargetFPS(60);
    }

    void EngineSystem::CleanUp()
    {
        CloseWindow();
    }
}
