#pragma once
#include "../screen/screen.h"

class Editor : public Screen {
public:
	Editor() = default;

	virtual void render() override;
	virtual void update() override;
};
