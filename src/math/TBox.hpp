#pragma once
#include <array>
#include <limits>
#include "../ThreeMacros.h"
THREE_NAMESPACE_BEGIN

template <class T, size_t dimension>
class TVector;

template <class T, size_t d1, size_t d2>
class TMatrix;

template <class T>
class TSphere;

template <class T>
class TPlane;

template <class T>
class TTriangle;

template <class T, size_t dimension>
class TBox {
#define THREE_DECLARE_BOX_COMMON_PART(dimension)                        \
    public:                                                             \
    typedef TVector<T, dimension> vec_t;                                \
    typedef TBox<T, dimension> type;                                    \
    typedef const TBox<T, dimension> const_type;                        \
    typedef std::numeric_limits<T> limit_t;                             \
    vec_t min, max;                                                     \
    TBox(vec_t min = vec_t().setAll(limit_t::max()),                    \
         vec_t max = vec_t().setAll(limit_t::min())) {                  \
        this->min = min;                                                \
        this->max = max;                                                \
    }                                                                   \
    type &set(const vec_t &min, const vec_t &max) {                     \
        this->min.copy(min);                                            \
        this->max.copy(max);                                            \
        return *this;                                                   \
    }                                                                   \
    template <class C>                                                  \
    type &setFromPoints(const C &container) {                           \
        this->makeEmpty();                                              \
        for (auto i = container.cbegin(); i != container.cend(); ++i) { \
            this->expandByPoint(*i);                                    \
        }                                                               \
        return *this;                                                   \
    }                                                                   \
    type &setFromPoints(const vec_t points[], size_t length) {          \
        this->makeEmpty();                                              \
        for (size_t i = 0; i < length; ++i) {                           \
            this->expandByPoint(points[i]);                             \
        }                                                               \
        return *this;                                                   \
    }                                                                   \
    type &setFromArray(T *array, size_t length) {                       \
        vec_t min;                                                      \
        vec_t max;                                                      \
        min.setAll(limit_t::max);                                       \
        min.setAll(limit_t::min);                                       \
        for (size_t i = 0; i < length; i += dimension) {                \
            for (size_t d = 0; d < dimension; ++d) {                    \
                if (array[i + d] < min[d]) {                            \
                    min[d] = array[i + d];                              \
                }                                                       \
                if (array[i + d] > max[d]) {                            \
                    max[d] = array[i + d];                              \
                }                                                       \
            }                                                           \
        }                                                               \
        this->min = min;                                                \
        this->max = max;                                                \
        return *this;                                                   \
    }                                                                   \
    type &setFromCenterAndSize(const vec_t &center, const vec_t &size) { \
        TVector<T, 2> _vector;                                          \
        auto halfSize = _vector.copy(size).multiplyScalar(0.5);         \
        this->min.copy(center).sub(halfSize);                           \
        this->max.copy(center).add(halfSize);                           \
        return *this;                                                   \
    }                                                                   \
    type clone() { return *this; }                                      \
    type &operator=(const_type &box) { return this->copy(box); }        \
    type &copy(const_type &box) {                                       \
        this->min.copy(box.min);                                        \
        this->max.copy(box.max);                                        \
        return *this;                                                   \
    }                                                                   \
    type &makeEmpty() {                                                 \
        this->min = vec_t().setAll(limit_t::max());                     \
        this->max = vec_t().setAll(limit_t::min());                     \
        return *this;                                                   \
    }                                                                   \
    bool isEmpty() {                                                    \
        for (int i = 0; i < dimension; ++i) {                           \
            if (this->max[i] < this->min[i]) {                          \
                return true;                                            \
            }                                                           \
        }                                                               \
        return false;                                                   \
    }                                                                   \
    vec_t getCenter() {                                                 \
        vec_t ret;                                                      \
        this->getCenter(ret);                                           \
        return ret;                                                     \
    }                                                                   \
    vec_t &getCenter(vec_t &target) {                                   \
        return this->isEmpty() ? target.setAll(T(0))                    \
            : target = (this->min+ this->max)                           \
            .multiplyScalar(0.5);                                       \
    }                                                                   \
    vec_t &getSize() {                                                  \
        vec_t ret;                                                      \
        this->getSize(ret);                                             \
        return ret;                                                     \
    }                                                                   \
    vec_t &getSize(vec_t &target) {                                     \
        return this->isEmpty() ? target.setAll(T(0))                    \
            : target.subVectors(this->max, this->min);                  \
    }                                                                   \
    type &expandByPoint(const vec_t &point) {                           \
        this->min.min(point);                                           \
        this->max.max(point);                                           \
        return *this;                                                   \
    }                                                                   \
    type &expandByVector(const vec_t &vector) {                         \
        this->min.sub(vector);                                          \
        this->max.add(vector);                                          \
        return *this;                                                   \
    }                                                                   \
    type &expandByScalar(T scalar) {                                    \
        this->min.addScalar(-scalar);                                   \
        this->max.addScalar(scalar);                                    \
        return *this;                                                   \
    }                                                                   \
    bool containsPoint(const vec_t &point) {                            \
        return point.x < this->min.x || point.x > this->max.x ||        \
            point.y < this->min.y || point.y > this->max.y              \
            ? false                                                     \
            : true;                                                     \
    }                                                                   \
    bool containsBox(const_type &box) {                                 \
        for (size_t i = 0; i < dimension; ++i) {                        \
            if (this->min[i] > box.min[i]) {                            \
                return false;                                           \
            }                                                           \
        }                                                               \
        return true;                                                    \
    }                                                                   \
    type &getParameter(const vec_t &point, vec_t &target = vec_t::zero()) { \
        for (size_t i = 0; i < dimension; ++i) {                        \
            target[i] =                                                 \
                (point[i] - this->min[i]) / (this->max[i] - this->min.x); \
        }                                                               \
        return target;                                                  \
    }                                                                   \
    bool intersectsBox(const_type &box) {                               \
        for (size_t i = 0; i < dimension; ++i) {                        \
            if (box.max[i] < this->min[i] || box.min[i] > this->max[i]) { \
                return false;                                           \
            }                                                           \
        }                                                               \
        return true;                                                    \
    }                                                                   \
    vec_t &clampPoint(const vec_t &point, vec_t &target) {              \
        return target.copy(point).clamp(this->min, this->max);          \
    }                                                                   \
    T distanceToPoint(const vec_t &point) {                             \
        TVector<T, 2> _vector;                                          \
        auto clampedPoint = _vector.copy(point).clamp(this->min, this->max); \
        return clampedPoint.sub(point).length();                        \
    }                                                                   \
    type &intersect(const_type &box) {                                  \
        this->min.max(box.min);                                         \
        this->max.min(box.max);                                         \
        return *this;                                                   \
    }                                                                   \
    type &Union(const_type &box) {                                      \
        this->min.min(box.min);                                         \
        this->max.max(box.max);                                         \
        return *this;                                                   \
    }                                                                   \
    type &translate(const vec_t &offset) {                              \
        this->min.add(offset);                                          \
        this->max.add(offset);                                          \
        return *this;                                                   \
    }                                                                   \
    bool equals(const_type &box) {                                      \
        return box.min.equals(this->min) && box.max.equals(this->max);  \
    }

    THREE_DECLARE_BOX_COMMON_PART(dimension)
};

template <class T>
class TBox<T, 3> {
    THREE_DECLARE_BOX_COMMON_PART(3)
    public:
    // setFromBufferAttribute( attribute )
    // setFromObject( object )
    // expandByObject( object ) {
    typedef TPlane<T> plane_t;
    typedef TTriangle<T> triangle_t;
    typedef TMatrix<T, 4, 4> matrix_t;
    typedef TSphere<T> sphere_t;
    bool intersectsSphere(const sphere_t &sphere) {
        vec_t _vector;

        // Find the point on the AABB closest to the sphere center.
        this->clampPoint(sphere.center, _vector);

        // If that point is inside the sphere, the AABB and sphere intersect.
        return _vector.distanceToSquared(sphere.center) <=
            (sphere.radius * sphere.radius);
    }
    bool intersectsPlane(const plane_t &plane) {
        // We compute the minimum and maximum dot product values. If those
        // values are on the same side (back or front) of the plane, then there
        // is no intersection.

        T min, max;

        if (plane.normal.x > 0) {
            min = plane.normal.x * this->min.x;
            max = plane.normal.x * this->max.x;

        } else {
            min = plane.normal.x * this->max.x;
            max = plane.normal.x * this->min.x;
        }

        if (plane.normal.y > 0) {
            min += plane.normal.y * this->min.y;
            max += plane.normal.y * this->max.y;

        } else {
            min += plane.normal.y * this->max.y;
            max += plane.normal.y * this->min.y;
        }

        if (plane.normal.z > 0) {
            min += plane.normal.z * this->min.z;
            max += plane.normal.z * this->max.z;

        } else {
            min += plane.normal.z * this->max.z;
            max += plane.normal.z * this->min.z;
        }

        return (min <= -plane.constant && max >= -plane.constant);
    }

    bool intersectsTriangle(const triangle_t &triangle) {
        if (this->isEmpty()) {
            return false;
        }

        vec_t _v0, _v1, _v2;
        vec_t _f0, _f1, _f2;
        vec_t _extents, _center, _triangleNormal;
        // compute box center and extents
        this->getCenter(_center);
        _extents.subVectors(this->max, _center);

        // translate triangle to aabb origin
        _v0.subVectors(triangle.a, _center);
        _v1.subVectors(triangle.b, _center);
        _v2.subVectors(triangle.c, _center);

        // compute edge vectors for triangle
        _f0.subVectors(_v1, _v0);
        _f1.subVectors(_v2, _v1);
        _f2.subVectors(_v0, _v2);

        // test against axes that are given by cross product combinations of the
        // edges of the triangle and the edges of the aabb make an axis testing
        // of each of the 3 sides of the aabb against each of the 3 sides of the
        // triangle = 9 axis of separation axis_ij = u_i x f_j (u0, u1, u2 =
        // face normals of aabb = x,y,z axes vectors since aabb is axis aligned)
        auto axes = {0,      -_f0.z, _f0.y, 0,      -_f1.z, _f1.y, 0,
            -_f2.z, _f2.y,  _f0.z, 0,      -_f0.x, _f1.z, 0,
            -_f1.x, _f2.z,  0,     -_f2.x, -_f0.y, _f0.x, 0,
            -_f1.y, _f1.x,  0,     -_f2.y, _f2.x,  0};
        if (!satForAxes(axes, _v0, _v1, _v2, _extents)) {
            return false;
        }

        // test 3 face normals from the aabb
        axes = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        if (!satForAxes(axes, _v0, _v1, _v2, _extents)) {
            return false;
        }

        // finally testing the face normal of the triangle
        // use already existing triangle edge vectors here
        _triangleNormal.crossVectors(_f0, _f1);
        axes = { _triangleNormal.x, _triangleNormal.y, _triangleNormal.z };

        return satForAxes(axes, _v0, _v1, _v2, _extents);
    }
    sphere_t getBoundingSphere() {
        sphere_t target;
        return getBoundingSphere(target);
    }
    sphere_t &getBoundingSphere(sphere_t &target) {

        this->getCenter(target.center);

        target.radius = this->getSize().length() * 0.5;

        return target;
    }
    type &applyMatrix4(const matrix_t &matrix) {
        vec_t _points[8];
        // transform of empty box is an empty box.
        if (this->isEmpty()) return this;

        // NOTE: I am using a binary pattern to specify all 2^3 combinations
        // below
        _points[0]
            .set(this->min.x, this->min.y, this->min.z)
            .applyMatrix4(matrix);  // 000
        _points[1]
            .set(this->min.x, this->min.y, this->max.z)
            .applyMatrix4(matrix);  // 001
        _points[2]
            .set(this->min.x, this->max.y, this->min.z)
            .applyMatrix4(matrix);  // 010
        _points[3]
            .set(this->min.x, this->max.y, this->max.z)
            .applyMatrix4(matrix);  // 011
        _points[4]
            .set(this->max.x, this->min.y, this->min.z)
            .applyMatrix4(matrix);  // 100
        _points[5]
            .set(this->max.x, this->min.y, this->max.z)
            .applyMatrix4(matrix);  // 101
        _points[6]
            .set(this->max.x, this->max.y, this->min.z)
            .applyMatrix4(matrix);  // 110
        _points[7]
            .set(this->max.x, this->max.y, this->max.z)
            .applyMatrix4(matrix);  // 111

        this->setFromPoints(_points);

        return *this;
    }

};
#undef THREE_DECLARE_BOX_COMMON_PART
THREE_NAMESPACE_END
