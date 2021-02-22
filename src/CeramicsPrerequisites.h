#pragma once
#include "CeramicsMacro.h"
#include <string>
CERAMICS_NAMESPACE_BEGIN

// CERAMICS default number type is float
typedef float Real;
// CERAMICS default string type is std::string
typedef std::string String;

template <class T> struct TMathUtils;
template <class T> struct TEuler;
template <class T> struct TQuaternion;
template <class T> struct TSphere;
template <class T> struct TPlane;
template <class T> struct TTriangle;
template <class T> struct TColor;
template <class T, size_t dimension> struct TVector;
template <class T, size_t dimension> struct TBox;
template <class T, size_t dimension> struct TLine;
template <class T, size_t rowNum, size_t colNum> struct TMatrix;

typedef TMathUtils<Real> MathUtils;
typedef TVector<Real, 2> Vector2;
typedef TVector<Real, 3> Vector3;
typedef TVector<Real, 4> Vector4;

typedef TMatrix<Real, 3, 3> Matrix3;
typedef TMatrix<Real, 4, 4> Matrix4;

typedef TQuaternion<Real> Quaternion;

typedef TEuler<Real> Euler;

typedef TLine<Real, 3> Line3;

typedef TBox<Real, 2> Box2;
typedef TBox<Real, 3> Box3;

typedef TSphere<Real> Sphere;
typedef TTriangle<Real> Triangle;
typedef TPlane<Real> Plane;

typedef TColor<Real> Color;
CERAMICS_NAMESPACE_END
