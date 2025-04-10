#pragma once
#include "json_parser.h"
#include <unordered_map>
#include <optional>
#include <filesystem>
#include <fstream>
#include "../../logging.h"

// import json type
using Json = nlohmann::json;

class Database {
public:
	Database() = default;

	// loading
	void load_directory(const std::string& path) {
		try {
			for (const auto& entry : std::filesystem::directory_iterator(path)) {
				if (entry.is_regular_file() && entry.path().extension() == ".json") {
					std::ifstream file(entry.path());
					if (file) {
						Json json_data;
						file >> json_data;
						m_data[entry.path().stem().string()] = json_data;
						AETHEREAL_LOG("Database::load_directory: Loaded JSON file: " << entry.path().string());
					}
					else {
						AETHEREAL_LOG("Database::load_directory: Failed to open file: " << entry.path().string());
					}
				}
			}
		}
		catch (const std::exception& e) {
			AETHEREAL_LOG("Database::load_directory: Error loading directory: " << e.what());
		}
	}

	Json* get_json(const std::string& path) {
		auto it = m_data.find(path);
		if (it != m_data.end()) {
			return &it->second;
		}
		else {
			AETHEREAL_LOG("Database::get_json: JSON not found at path: " << path);
			return nullptr;
		}
	}

private:
	std::unordered_map<std::string, Json> m_data;
};
