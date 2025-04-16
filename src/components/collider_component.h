#pragma once
#include <functional>

struct ColliderComponent {
	std::function<bool(void)> on_collision;	
};
