#pragma once

namespace Aethereal::Core
{
    class ISystem
    {
    public:
        ISystem() = default;
        virtual ~ISystem() = default;

        virtual void Create();
        virtual void Step();
        virtual void Draw();
        virtual void CleanUp();
    };
}
