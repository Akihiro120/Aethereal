#include "game.h"
#include <chrono>
#include <thread>

// ftxui
#include <ftxui/component/component.hpp>

// Aethereal
#include "../services/service_locator/service_locator.h"
#include "../screen/manager/screen_manager.h"

namespace Aethereal
{
    using namespace ftxui;

    Aethereal::Aethereal()
        : m_InteractiveScreen(ScreenInteractive::Fullscreen()),
          m_ComponentRoot(ConstructSceneRoot()),
          m_RenderLoop(&m_InteractiveScreen, m_ComponentRoot)
    {
    }

    Component Aethereal::ConstructSceneRoot()
    {
        auto sl = Service::ServiceLocator::Get<Screen::ScreenManager>();

        // Construct the scene root
        Component root = Renderer(sl->GetRootComponent(), [&]
        {
            return sl->GetRootComponent()->Render();
        });

        // Define input controls
        root |= CatchEvent([&](Event e)
        {
            if (e == Event::Character('q'))
            {
                // Quit the game, close the window
                m_InteractiveScreen.ExitLoopClosure()();
                return true;
            }
            return false;
        });

        return root;
    }

    Aethereal::~Aethereal()
    {
        // Clean up and free resources.
        Clean();
    }

    void Aethereal::Run()
    {
        // Define the frame time
        const auto frameTime = std::chrono::milliseconds(1000 / 60);

        // Render loop.
        while (m_Running && !m_RenderLoop.HasQuitted())
        {
            // Progress the game's lifecycle.
            Update();

            // Render and display components to screen.
            Render();

            // Delay the main thread for ~16ms
            std::this_thread::sleep_for(frameTime);
        }
    }

    void Aethereal::Render()
    {
        // Run the rendering once
        m_RenderLoop.RunOnce();
    }

    void Aethereal::Update()
    {
    }

    void Aethereal::Clean()
    {
    }
}
