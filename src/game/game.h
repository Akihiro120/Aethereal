#pragma once
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/loop.hpp>

namespace Aethereal
{
    using namespace ftxui;

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

        Component ConstructSceneRoot();

        ScreenInteractive m_InteractiveScreen;
        Component m_ComponentRoot;
        Loop m_RenderLoop;

        bool m_Running = true;
    };
}
