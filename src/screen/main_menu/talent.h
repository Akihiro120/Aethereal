#pragma once
#include "../screen.h"

class TalentScreen : public Screen {
public:
	TalentScreen() = default;

	virtual void render() override;
	virtual void update() override;

private:
	int m_selected = 0;
	int m_num_talents = 0;
};
