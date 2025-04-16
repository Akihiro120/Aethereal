#pragma once
#include <functional>

struct ColliderComponent {
	// TODO: Implement per tile collision for larger objects
	std::vector<bool> collision_tiles;
	std::function<bool(void)> on_collision;	
};
