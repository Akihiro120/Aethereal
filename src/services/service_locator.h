#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <iostream>

class ServiceLocator {
public:
	// Delete copy and move constructors and assignment operators
	ServiceLocator(const ServiceLocator&) = delete;
	ServiceLocator(ServiceLocator&&) = delete;
	ServiceLocator& operator=(const ServiceLocator&) = delete;
	ServiceLocator& operator=(ServiceLocator&&) = delete;

	// provide service
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

	// get service
	template <typename T>
	static std::shared_ptr<T> get_service() {
		const std::type_index type_index = std::type_index(typeid(T));

		auto it = get().m_services.find(type_index);
		if (it == get().m_services.end()) {
			throw std::runtime_error("Service not provided");
		}

		auto service = std::static_pointer_cast<T>(it->second);
		if (!service) {
			throw std::runtime_error("Service type mismatch");
		}
		return service;
	}

private:
	static ServiceLocator& get() {
		static ServiceLocator instance;
		return instance;
	}

	ServiceLocator() = default;

	// service
	std::unordered_map<std::type_index, std::shared_ptr<void>> m_services;
};
