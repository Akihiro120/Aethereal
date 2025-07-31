#pragma once
#include "../ecs/system/core/systemManager.h"

namespace Aethereal
{
    class Game
    {
    public:
        Game();
        ~Game();

        void Run();

    private:
        void Step();
        void Draw();
        void Create();
        void CleanUp();

    private:
        Core::SystemManager m_SystemManager = {};
    };
}
