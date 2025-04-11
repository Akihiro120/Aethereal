#pragma once
#include "../screen.h"

class SpeciesScreen : public Screen {
public:
	SpeciesScreen() = default;

	virtual void render() override;
	virtual void update() override;

private:
	int m_selected = 0;
	int m_num_species = 0;
};
