#pragma once
#include "json_parser.h"
#include <unordered_map>
#include <optional>
#include <filesystem>
#include <fstream>
#include "../../logging.h"

// import json type
using Json = nlohmann::json;

struct DatabaseEntry {
	std::string path;
	Json json_data;
};

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
						m_data[entry.path().stem().string()].json_data = json_data;
						m_data[entry.path().stem().string()].path = entry.path().string();
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

	void hot_reload(const std::string& path) {
		if (m_data.find(path) == m_data.end()) {
			AETHEREAL_LOG("Database::hot_reload: Path not found in database: " << path);
			return;
		}

		std::ifstream file(m_data[path].path);	
		if (file) {
			// read the json file
			Json json_data;
			try {
				file >> json_data;
			} catch (const std::exception& e) {
				AETHEREAL_LOG("Database::hot_reload: Error parsing JSON file: " << e.what());
				return;
			}
			m_data[path].json_data = json_data;
			AETHEREAL_LOG("Database::hot_reload: Reloaded JSON file: " << m_data[path].path);

		} else {
			AETHEREAL_LOG("Database::hot_reload: Failed to open file: " << path);
		}
		file.close();
	}

	Json* get_json(const std::string& path) {
		auto it = m_data.find(path);
		if (it != m_data.end()) {
			return &it->second.json_data;
		}
		else {
			AETHEREAL_LOG("Database::get_json: JSON not found at path: " << path);
			return nullptr;
		}
	}

private:
	std::unordered_map<std::string, DatabaseEntry> m_data;
};
