#pragma once
#include <string>
#include "../screen.h"

class NameScreen : public Screen {
public:
	NameScreen() = default;

	virtual void render() override;
	virtual void update() override;

private:
	std::string m_name = "";
};
