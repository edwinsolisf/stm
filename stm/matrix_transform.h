#ifndef stm_matrix_transform_h
#define stm_matrix_transform_h

#include "vector.h"
#include "matrix.h"

namespace stm
{

	constexpr const vec3f posX = { 1.0f, 0.0f, 0.0f };
	constexpr const vec3f negX = {-1.0f, 0.0f, 0.0f };
	constexpr const vec3f posY = { 0.0f, 1.0f, 0.0f };
	constexpr const vec3f negY = { 0.0f,-1.0f, 0.0f };
	constexpr const vec3f posZ = { 0.0f, 0.0f, 1.0f };
	constexpr const vec3f negZ = { 0.0f, 0.0f,-1.0f };

	mat4f scale(const vec3f& scaleFactor) noexcept;
	mat4f scale(const float xScale, const float yScale, const float zScale) noexcept;

	mat4f translate(const vec3f& translateFactor) noexcept;
	mat4f translate(const float xTrans, const float yTrans, const float zTrans) noexcept;

	mat4f rotateX(const float angleInRads) noexcept;
	mat4f rotateY(const float angleInRads) noexcept;
	mat4f rotateZ(const float angleInRads) noexcept;
	mat4f rotate(const vec3f& axis, const float angleInRads) noexcept;
    vec3f rotation(const vec3f& vec, const vec3f& axis, const float angle) noexcept;

	mat4f ortho(const float xleft, const float xright, const float ybottom, const float ytop, const float znear, const float zfar) noexcept;
	mat4f perspective(const float FOVRads, const float aspectRatio, const float zNear, const float zFar) noexcept;
    mat4f lookAt(const vec3f& position, const vec3f& up, const vec3f& right) noexcept;
    mat4f lookAt(const vec3f& position, const vec3f& up, const vec3f& right, const vec3f& direction) noexcept;
}
#endif /* stm_matrix_transform_h */