#ifndef stm_function_h
#define stm_function_h

#include <cmath>

namespace stm
{
	static inline float logisticf(float value) noexcept { return 1.0f / (1.0f + exp(-value)); }
	static inline double logistic(double value) noexcept { return 1.0 / (1.0 + exp(-value)); }

	static float logistic_primef(float value) noexcept { return logisticf(value) * (1.0f - logisticf(value)); }
	static double logistic_prime(double value) noexcept { return logistic(value) * (1.0 - logistic(value)); }
}


#endif /* stm_function_h */
