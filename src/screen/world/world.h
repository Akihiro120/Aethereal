#pragma once
#include "../screen.h"

class World : public Screen {
public:
	World() = default;

	void render() override;
	void update() override;
};
