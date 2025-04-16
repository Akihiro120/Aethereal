#pragma once
#include <vector>
#include <functional>
#include <fecs.h>

struct Item {
	// item data
	std::string name = "";
	std::string desc = "";

	// item functionality
	std::function<void(std::shared_ptr<FECS>)> on_usage;
	std::function<void(std::shared_ptr<FECS>)> on_remove;
	std::function<void(std::shared_ptr<FECS>)> on_pickup;
};

struct InventoryItem {
	Item item;
	uint32_t amount;
};

struct InventoryComponent {
	std::vector<InventoryItem> items;
};

// inventory callback/delegate components
struct InventoryInsert {
	InventoryItem added_item;
};

struct InventoryRemove {
	uint32_t index;
	uint32_t amount;
};
