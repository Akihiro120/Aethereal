#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "../../utility/logging.h"

namespace Aethereal::Service
{
    class ServiceLocator
    {
    public:
        template <typename T>
        static void RegisterService(std::shared_ptr<T> srv)
        {
            auto it = Get().m_Services.find(typeid(T));
            if (it != Get().m_Services.end())
            {
                Utility::ERROR("Service Locator: Service already Registered");
            }

            Get().m_Services[typeid(T)] = std::move(srv);
        }

        template <typename T>
        static std::shared_ptr<T> Get()
        {
            auto it = Get().m_Services.find(typeid(T));
            if (it == Get().m_Services.end())
            {
                Utility::ERROR("Service Locator: Service not Found: " + std::string(typeid(T).name()));
            }

            return std::static_pointer_cast<T>(it->second);
        }

    private:
        ServiceLocator() = default;

        static ServiceLocator& Get()
        {
            static ServiceLocator instance;
            return instance;
        }

        std::unordered_map<std::type_index, std::shared_ptr<void>> m_Services;
    };
}
