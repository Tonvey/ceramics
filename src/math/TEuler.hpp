#pragma once
#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <initializer_list>
#include "../utils/TProperty.hpp"
#include "TMathUtils.hpp"
#include "../CeramicsPrerequisites.h"
#include "ERotationOrder.h"
CERAMICS_NAMESPACE_BEGIN
template <class T>
struct TEuler
{
    typedef T value_type;
    typedef TEuler<T> type;
    static RotationOrder DefaultOrder;
    T x, y, z;
    RotationOrder order = XYZ;
    TEuler(T x = 0, T y = 0, T z = 0, RotationOrder order = DefaultOrder)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->order = order;
    }

    void set(T x, T y, T z, RotationOrder order)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->order = order;

        // TODO change callback
    }

    type &operator=(const type &other)
    {
        this->set(other.x, other.y, other.z, other.order);
        return *this;
    }

    void setFromRotationMatrix(TMatrix<T, 4, 4> m, RotationOrder order = XYZ)
    {
        auto clamp = TMathUtils<T>::clamp;

        // assumes the upper 3x3 of m is a pure rotation matrix (i.e, unscaled)
        auto &te = m.elements;
        auto m11 = te[0], m12 = te[1], m13 = te[2];
        auto m21 = te[4], m22 = te[5], m23 = te[6];
        auto m31 = te[8], m32 = te[9], m33 = te[10];

        switch (order)
        {
        case RotationOrder::XYZ:

            this->y = std::asin(clamp(m13, -1, 1));

            if (std::abs(m13) < 0.9999999)
            {
                this->x = std::atan2(-m23, m33);
                this->z = std::atan2(-m12, m11);

            }
            else
            {
                this->x = std::atan2(m32, m22);
                this->z = 0;
            }

            break;

        case RotationOrder::YXZ:

            this->x = std::asin(-clamp(m23, -1, 1));

            if (std::abs(m23) < 0.9999999)
            {
                this->y = std::atan2(m13, m33);
                this->z = std::atan2(m21, m22);

            }
            else
            {
                this->y = std::atan2(-m31, m11);
                this->z = 0;
            }

            break;

        case RotationOrder::ZXY:

            this->x = std::asin(clamp(m32, -1, 1));

            if (std::abs(m32) < 0.9999999)
            {
                this->y = std::atan2(-m31, m33);
                this->z = std::atan2(-m12, m22);

            }
            else
            {
                this->y = 0;
                this->z = std::atan2(m21, m11);
            }

            break;

        case RotationOrder::ZYX:

            this->y = std::asin(-clamp(m31, -1, 1));

            if (std::abs(m31) < 0.9999999)
            {
                this->x = std::atan2(m32, m33);
                this->z = std::atan2(m21, m11);

            }
            else
            {
                this->x = 0;
                this->z = std::atan2(-m12, m22);
            }

            break;

        case RotationOrder::YZX:

            this->z = std::asin(clamp(m21, -1, 1));

            if (std::abs(m21) < 0.9999999)
            {
                this->x = std::atan2(-m23, m22);
                this->y = std::atan2(-m31, m11);

            }
            else
            {
                this->x = 0;
                this->y = std::atan2(m13, m33);
            }

            break;

        case RotationOrder::XZY:

            this->z = std::asin(-clamp(m12, -1, 1));

            if (std::abs(m12) < 0.9999999)
            {
                this->x = std::atan2(m32, m22);
                this->y = std::atan2(m13, m11);

            }
            else
            {
                this->x = std::atan2(-m23, m33);
                this->y = 0;
            }

            break;

        default:

            // TODO
            // console.warn( 'CERAMICS.Euler: .setFromRotationMatrix()
            // encountered an unknown order: ' + order );
            break;
        }

        this->order = order;

    }

    void setFromQuaternion(TQuaternion<T> q, RotationOrder order = XYZ)
    {
        auto matrix = TMatrix<T, 4, 4>::makeRotationFromQuaternion(q);

        return this->setFromRotationMatrix(matrix, order);
    }

    void setFromVector3(TVector<T, 3> v, RotationOrder order = XYZ)
    {
        return this->set(v.x(), v.y(), v.z(), order);
    }

    void reorder(RotationOrder newOrder)
    {
        // WARNING: this discards revolution information -bhouston

        TQuaternion<T> _quaternion;
        _quaternion.setFromEuler(this);

        return this->setFromQuaternion(_quaternion, newOrder);
    }

    bool equals(const type &euler)
    {
        return (euler->x == this->x) && (euler->y == this->y) &&
            (euler->z == this->z) && (euler.order == this->order);
    }

    template <class array_t>
    type &fromArray(array_t array)
    {
        this->x = array[0];
        this->y = array[1];
        this->z = array[2];
        // if ( array[ 3 ] !== undefined )
        this->order = array[3];

        return *this;
    }

    template <class array_t>
    array_t toArray(array_t array, int offset)
    {
        // if ( array === undefined ) array = [];
        // if ( offset === undefined ) offset = 0;

        array[offset] = this->x;
        array[offset + 1] = this->y;
        array[offset + 2] = this->z;
        array[offset + 3] = this->order;

        return array;
    }

    TVector<T, 3> toVector3()
    {
        return TVector<T, 3>(this->x, this->y, this->z);
    }

};
template <class T>
RotationOrder TEuler<T>::DefaultOrder = XYZ;
CERAMICS_NAMESPACE_END
