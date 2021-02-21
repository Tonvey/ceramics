#pragma once
#include "TBox.hpp"
#include "../CeramicsMacro.h"
CERAMICS_NAMESPACE_BEGIN
template <class T, size_t dimension>
class TVector;

template <class T, size_t d1, size_t d2>
class TMatrix;

template <class T, size_t dimension>
class TBox;

template<class T>
class TPlane;

template <class T>
class TSphere
{
public:
    typedef TSphere<T> type;
    typedef const TSphere<T> const_type;
    typedef TBox<T, 3> box_t;
    typedef TVector<T, 3> vec_t;
    typedef TPlane<T> plane_t;
    vec_t center;
    T radius;
    TSphere(vec_t center = vec_t(), T radius = T(-1))
    {
        this->center = center;
        this->radius = radius;
    }

    type &set(const vec_t &center, T radius)
    {
        this->center.copy(center);
        this->radius = radius;

        return *this;
    }

    template<class C>
    type &setFromPoints(const C &container,
                        const vec_t &optionalCenter)
    {
        auto &center = this->center;
        center.copy(optionalCenter);

        T maxRadiusSq = 0;

        for (auto i = container.cbegin(); i != container.cend(); ++i)
        {
            maxRadiusSq =
                std::max(maxRadiusSq, center.distanceToSquared(*i));
        }

        this->radius = std::sqrt(maxRadiusSq);
        return *this;
    }
    template<class C>
    type &setFromPoints(const C &container)
    {
        box_t _box;
        vec_t center;

        _box.setFromPoints(container).getCenter(center);

        return this->setFromPoints(container, center);
    }
    type &setFromPoints(vec_t points[], size_t length,
                        const vec_t &optionalCenter)
    {
        auto &center = this->center;
        center.copy(optionalCenter);

        T maxRadiusSq = 0;

        for (size_t i = 0; i < length; i++)
        {
            maxRadiusSq =
                std::max(maxRadiusSq, center.distanceToSquared(points[i]));
        }

        this->radius = std::sqrt(maxRadiusSq);
        return *this;
    }
    type &setFromPoints(vec_t points[], size_t length)
    {
        box_t _box;
        vec_t center;

        _box.setFromPoints(points).getCenter(center);

        return this->setFromPoints(points, length, center);
    }

    type clone() { return *this; }

    type &operator=(const_type &sphere) { return this->copy(sphere); }
    type &copy(const_type &sphere)
    {
        this->center.copy(sphere.center);
        this->radius = sphere.radius;

        return *this;
    }

    bool isEmpty() { return (this->radius < T(0)); }

    type &makeEmpty()
    {
        this->center.setAll(T(0));
        this->radius = T(-1);

        return *this;
    }

    bool containsPoint(const vec_t &point)
    {
        return (point.distanceToSquared(this->center) <=
                (this->radius * this->radius));
    }

    T distanceToPoint(const vec_t &point)
    {
        return (point.distanceTo(this->center) - this->radius);
    }

    bool intersectsSphere(const_type &sphere)
    {
        auto radiusSum = this->radius + sphere.radius;

        return sphere.center.distanceToSquared(this->center) <=
            (radiusSum * radiusSum);
    }

    bool intersectsBox(const box_t &box) { return box.intersectsSphere(*this); }

    bool intersectsPlane(const plane_t &plane)
    {
        return std::abs(plane.distanceToPoint(this->center)) <= this->radius;
    }

    vec_t &clampPoint(const vec_t &point, vec_t &target)
    {
        auto deltaLengthSq = this->center.distanceToSquared(point);

        target.copy(point);

        if (deltaLengthSq > (this->radius * this->radius))
        {
            target.sub(this->center).normalize();
            target.multiplyScalar(this->radius).add(this->center);
        }

        return target;
    }

    box_t &getBoundingBox(box_t &target)
    {
        if (this->isEmpty())
        {
            // Empty sphere produces empty bounding box
            target.makeEmpty();
            return target;
        }

        target.set(this->center, this->center);
        target.expandByScalar(this->radius);

        return target;
    }

    type &applyMatrix4(TMatrix<T, 4, 4> matrix)
    {
        this->center.applyMatrix4(matrix);
        this->radius = this->radius * matrix.getMaxScaleOnAxis();

        return *this;
    }

    type &translate(const vec_t &offset)
    {
        this->center.add(offset);

        return *this;
    }

    bool operator==(const_type &sphere) { return this->equals(sphere); }
    bool equals(const_type &sphere)
    {
        return sphere.center.equals(this->center) &&
            (sphere->radius == this->radius);
    }
};
CERAMICS_NAMESPACE_END
