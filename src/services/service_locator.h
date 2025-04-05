#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <iostream>

class ServiceLocator {
public:
	template <typename T>
	static void provide(std::shared_ptr<T> service) {
		const std::type_index type_index = std::type_index(typeid(T));	

		auto it = get().m_services.find(type_index);
		if (it != get().m_services.end()) {
			std::cout << "Service already provided for this type." << std::endl;
			return;
		}

		get().m_services[type_index] = service;
		return;
	}

	template <typename T>
	static T& get_service() {
		const std::type_index type_index = std::type_index(typeid(T));

		auto it = get().m_services.find(type_index);
		if (it == get().m_services.end()) {
			throw std::runtime_error("Service not provided");
		}

		return *std::static_pointer_cast<T>(it->second);
	}

private:
	static ServiceLocator& get() {
		static ServiceLocator instance;
		return instance;
	}

	ServiceLocator() = default;

	std::unordered_map<std::type_index, std::shared_ptr<void>> m_services;
};
