#pragma once
#include <math.h>

namespace FWMath {
	 
	 template<typename T>
	 static T clamp(T x, T minimum, T maximum) {
		  
		  return std::max(minimum, std::min(x, maximum));
	 }
}
