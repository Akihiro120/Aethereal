#pragma once

struct VelocityComponent {
	float x = 0.0f;
	float y = 0.0f;

	VelocityComponent() = default;
	VelocityComponent(float x, float y) : x(x), y(y) {}
	VelocityComponent(int x, int y) : x((float)x), y((float)y) {}
};
