#ifndef stm_math_h
#define stm_math_h

#include "matrix.h"
#include "dynamic_matrix.h"
#include "matrix_transform.h"
#include "vector.h"
#include "dynamic_vector.h"
#include "distribution.h"
#include "function.h"
#include "quaternion.h"
#include "utilities.h"
#include "constants.h"
#include "debug.h"

namespace stm
{
	inline float radians(const float& angleInDegs) { return angleInDegs * PI_f / 180.0f; }
	inline double radians(const double& angleInDegs) { return angleInDegs * PI / 180.0; }

	inline float degrees(const float& angleInRads) { return angleInRads * 180.0f / PI_f; }
	inline double degrees(const double& angleInRads) { return angleInRads * 180.0 / PI; }

	inline float angle(const vec3f& vec1, const vec3f& vec2) { return acos(dotproduct(vec1, vec2) / (vec1.Magnitude() * vec2.Magnitude())); }
	inline double angle(const vector<double, 3>& vec1, const vector<double, 3>& vec2) { return acos(vec1.DotProduct(vec2)) / (vec1.Magnitude() * vec2.Magnitude()); }
}
#endif /* stm_math_h */