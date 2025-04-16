#pragma once
#include <iostream>

#ifndef DEBUG
// assert
#define AETHEREAL_ASSERT(expr, log) \
	do { \
		if (!(expr)) { \
			std::cerr << "Assertion failed: " << log << std::endl; \
			std::abort(); \
		} \
	} while (0)

// log
#define AETHEREAL_LOG(msg) \
	do { \
		std::cout << msg << std::endl; \
	} while (0)
#else
#define AETHEREAL_ASSERT(expr) \
	((void)0)
#define AETHEREAL_LOG(msg) \
	((void)0)
#endif

