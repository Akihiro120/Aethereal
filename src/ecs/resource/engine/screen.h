#pragma once

namespace Aethereal::ECS::Resource::Engine
{
    class IScreen
    {
    public:
        IScreen() = default;

        virtual void Create();
        virtual void Step();
        virtual void Draw();
        virtual void CleanUp();

    private:
    };
}
