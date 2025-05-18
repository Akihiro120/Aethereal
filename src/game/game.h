#pragma once

namespace Aethereal
{
    class Aethereal
    {
    public:
        Aethereal();
        ~Aethereal();

        void Run();

    private:
        void RegisterServices();
        void InitializeECS();
        void LoadDatabase();
        void InitialTerminal();
        void SetInitialScreen();
        void Update();
        void Render();
        void Clean();
    };
}
