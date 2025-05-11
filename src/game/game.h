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
        void Update();
        void Render();
        void Clean();
    };
}
