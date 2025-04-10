#pragma once
#include "json_parser.h"

// import json type
using Json = nlohmann::json;

class Database {
public:
	Database();

	// loading
	void load_directory(const std::string& path);

	// data reading

private:
	std::vector<Json> m_data;
};
