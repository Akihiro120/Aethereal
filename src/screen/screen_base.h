#pragma once
#include "screen_interface.h"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/deprecated.hpp>

namespace Aethereal::Screen
{
    class ScreenBase : public IScreen
    {
    public:
        ScreenBase()
        {
            ConstructSceneRoot();
        }

        ~ScreenBase() = default;

        ftxui::Component GetComponentRoot()
        {
            return m_Component;
        }

        ftxui::Component GetComponentContainer()
        {
            return m_Container;
        }

    protected:
        virtual ftxui::Component CreateComponentRoot()
        {
            return ftxui::Renderer([&]
            {
                return ftxui::text("Empty Screen") | ftxui::bold;
            });
        }

        virtual ftxui::Component CreateComponentContainer()
        {
            return ftxui::Container::Vertical({});
        }

        void ConstructSceneRoot()
        {
            m_Component = CreateComponentRoot();
            m_Container = CreateComponentContainer();
        }

        ftxui::Component m_Component;
        ftxui::Component m_Container;
    };
}
