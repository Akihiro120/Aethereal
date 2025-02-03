#pragma once
#include <fecs/FECS.h>

struct NameComponent {
	 std::string name;

	 NameComponent(const std::string& str) {
		  name = str;
	 }
};
