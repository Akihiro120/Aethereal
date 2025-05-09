#pragma once
#include <ftxui/component/component.hpp>

using namespace ftxui;

namespace Aethereal::Screen
{
    class IScreen
    {
    public:
        virtual ~IScreen() = default;

        // Return the root component of the screen
        virtual Component GetComponent() const = 0;
    };
}
