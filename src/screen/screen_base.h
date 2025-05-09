#pragma once
#include "screen_interface.h"

namespace Aethereal::Screen
{
    class ScreenBase : public IScreen
    {
    public:
        ScreenBase(Component root)
            : m_RootComponent(root)
        {
        }

        ~ScreenBase() = default;

        virtual Component GetComponent() const override
        {
            return m_RootComponent;
        }

    protected:
        Component m_RootComponent;
    };
}
