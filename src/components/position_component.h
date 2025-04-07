#pragma once

struct Position {
	float x = 0.0f;
	float y = 0.0f;

	Position() = default;
	Position(float x, float y) : x(x), y(y) {}
	Position(int x, int y) : x((float)x), y((float)y) {}
};
