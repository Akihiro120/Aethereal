#include "empty.h"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

namespace Aethereal::Screen
{
    Empty::Empty()
    {
    }

    ftxui::Component Empty::CreateComponentRoot()
    {
        return ftxui::Renderer([&]
        {
            return ftxui::text("No valid scren attached to the layer!!!.");
        });
    }
}
