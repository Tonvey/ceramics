#pragma once
#include <string>
#include <type_traits>

#include "CeramicsMacro.h"
#include "math/TBox.hpp"
#include "math/TColor.hpp"
#include "math/TEuler.hpp"
#include "math/TLine.hpp"
#include "math/TMathUtils.hpp"
#include "math/TMatrix.hpp"
#include "math/TPlane.hpp"
#include "math/TQuaternion.hpp"
#include "math/TSphere.hpp"
#include "math/TTriangle.hpp"
#include "math/TVector.hpp"
CERAMICS_NAMESPACE_BEGIN
#define null nullptr;
// CERAMICS default number type is float
typedef float number_t;
// CERAMICS default string type is std::string
typedef std::string String;

typedef TMathUtils<number_t> MathUtils;
typedef TVector<number_t, 2> Vector2;
typedef TVector<number_t, 3> Vector3;
typedef TVector<number_t, 4> Vector4;

typedef TMatrix<number_t, 3, 3> Matrix3;
typedef TMatrix<number_t, 4, 4> Matrix4;

typedef TQuaternion<number_t> Quaternion;

typedef TEuler<number_t> Euler;

typedef TLine<number_t, 3> Line3;

typedef TBox<number_t, 2> Box2;
typedef TBox<number_t, 3> Box3;

typedef TSphere<number_t> Sphere;
typedef TTriangle<number_t> Triangle;
typedef TPlane<number_t> Plane;

typedef TColor<number_t> Color;
CERAMICS_NAMESPACE_END
