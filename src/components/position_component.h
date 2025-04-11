#pragma once

struct PositionComponent {
	float x = 0.0f;
	float y = 0.0f;

	PositionComponent() = default;
	PositionComponent(float x, float y) : x(x), y(y) {}
	PositionComponent(int x, int y) : x((float)x), y((float)y) {}
};
