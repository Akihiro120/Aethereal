#pragma once
#include <vector>
#include <functional>
#include <fecs.h>
#include <memory>

struct ItemComponent {
	// item data
	std::string name = "";
	std::string desc = "";
    int amount = 0;

	// item functionality
	std::function<void(std::shared_ptr<FECS>)> on_usage;
	std::function<void(std::shared_ptr<FECS>)> on_remove;
	std::function<void(std::shared_ptr<FECS>)> on_pickup;
};

struct InventoryComponent {
	std::vector<ItemComponent> items;
};

// inventory callback/delegate components
struct InventoryAddItemComponent {
    ItemComponent item;
};

struct InventoryRemoveItemComponent {
	uint32_t index;
	uint32_t amount;
};
