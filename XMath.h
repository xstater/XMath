#ifndef _XMATH_H_
#define _XMATH_H_

#include "Matrix.h"
#include "Vector.h"
#include "Tools.h"

namespace xmath{
    using vec2 = Vector2d<float>;
    using dvec2 = Vector2d<double>;
    using ivec2 = Vector2d<int>;
    using uvec2 = Vector2d<unsigned int>;

    using vec3 = Vector3d<float>;
    using dvec3 = Vector3d<double>;
    using ivec3 = Vector3d<int>;
    using uvec3 = Vector3d<unsigned int>;

    using vec4 = Vector4d<float>;
    using dvec4 = Vector4d<double>;
    using ivec4 = Vector4d<int>;
    using uvec4 = Vector4d<unsigned int>;

    using mat3 = Matrix3d<float>;
    using dmat3 = Matrix3d<double>;
    using imat3 = Matrix3d<int>;
    using umat3 = Matrix3d<unsigned int>;

    using mat4 = Matrix4d<float>;
    using dmat4 = Matrix4d<double>;
    using imat4 = Matrix4d<int>;
    using umat4 = Matrix4d<unsigned int>;
}

#endif //_XMATH_H_
