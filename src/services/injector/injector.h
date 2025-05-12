#pragma once
#include <tuple>
#include <memory>
#include "../service_locator/service_locator.h"

namespace Aethereal::Service
{
    template <typename Derived, typename... Deps>
    class Injector
    {
    public:
        Injector()
            : m_Dependencies(ServiceLocator::Get<Deps>()...)
        {
        }

        template <typename T>
        std::shared_ptr<T> GetInjection()
        {
            return std::get<std::shared_ptr<T>>(m_Dependencies);
        }

    private:
        std::tuple<std::shared_ptr<Deps>...> m_Dependencies;
    };
}
