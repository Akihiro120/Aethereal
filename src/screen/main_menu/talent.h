#pragma once
#include "../screen.h"

class TalentScreen : public Screen {
public:
	TalentScreen() = default;

	virtual void render() override;
	virtual void update() override;
};
