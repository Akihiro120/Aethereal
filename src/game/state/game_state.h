#pragma once

namespace Aethereal
{
    namespace State
    {
        class GameState
        {
        public:
            GameState();
            ~GameState() = default;

            bool IsGameRunning();
            void StopRunning();

        private:
            bool m_Running = true;
        };
    }
}
