#pragma once

struct Velocity {
	float x = 0.0f;
	float y = 0.0f;

	Velocity() = default;
	Velocity(float x, float y) : x(x), y(y) {}
	Velocity(int x, int y) : x((float)x), y((float)y) {}
};
