#pragma once
#include <cassert>
#include <cmath>
#include <functional>
#include <initializer_list>
#include <limits>
#include <stdexcept>

#include "../utils/TProperty.hpp"
#include "TMathUtils.hpp"
#include "ERotationOrder.h"
#include "../CeramicsPrerequisites.h"
CERAMICS_NAMESPACE_BEGIN
template <class T>
struct TQuaternion
{
    typedef T value_type;
    typedef TQuaternion<T> type;
    // typedef std::function<void()> callback_type;
    friend TMatrix<T, 4, 4>;
    // TODO change callback
    //TProperty<T> x, y, z, w;
    TQuaternion(T x = T(0), T y = T(0), T z = T(0), T w = T(1))
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    static type slerp(type qa, type qb, T t)
    {
        type qm = qa;
        return qm.slerp(qb, t);
    }

    static type slerpFlat(type dst, T dstOffset, type src0, T srcOffset0,
                          type src1, T srcOffset1, T t)
    {
        // fuzz-free, array-based Quaternion SLERP operation
        auto x0 = src0[srcOffset0 + 0], y0 = src0[srcOffset0 + 1],
            z0 = src0[srcOffset0 + 2], w0 = src0[srcOffset0 + 3];
        auto x1 = src1[srcOffset1 + 0], y1 = src1[srcOffset1 + 1],
            z1 = src1[srcOffset1 + 2], w1 = src1[srcOffset1 + 3];
        if (w0 != w1 || x0 != x1 || y0 != y1 || z0 != z1)
        {
            auto s = 1 - t;
            const auto cos = x0 * x1 + y0 * y1 + z0 * z1 + w0 * w1,
                dir = (cos >= 0 ? 1 : -1), sqrSin = 1 - cos * cos;

            // Skip the Slerp for tiny steps to avoid numeric problems:
            if (sqrSin > std::numeric_limits<T>::epsilon())
            {
                const auto sin = std::sqrt(sqrSin),
                    len = std::atan2(sin, cos * dir);

                s = std::sin(s * len) / sin;
                t = std::sin(t * len) / sin;
            }

            const auto tDir = t * dir;

            x0 = x0 * s + x1 * tDir;
            y0 = y0 * s + y1 * tDir;
            z0 = z0 * s + z1 * tDir;
            w0 = w0 * s + w1 * tDir;

            // Normalize in case we just did a lerp:
            if (s == 1 - t)
            {
                const auto f =
                    1 / std::sqrt(x0 * x0 + y0 * y0 + z0 * z0 + w0 * w0);

                x0 *= f;
                y0 *= f;
                z0 *= f;
                w0 *= f;
            }
        }

        dst[dstOffset] = x0;
        dst[dstOffset + 1] = y0;
        dst[dstOffset + 2] = z0;
        dst[dstOffset + 3] = w0;
    }
    // static multiplyQuaternionsFlat( dst, dstOffset, src0, srcOffset0, src1,
    // srcOffset1 ) {

    // 	const x0 = src0[ srcOffset0 ];
    // 	const y0 = src0[ srcOffset0 + 1 ];
    // 	const z0 = src0[ srcOffset0 + 2 ];
    // 	const w0 = src0[ srcOffset0 + 3 ];

    // 	const x1 = src1[ srcOffset1 ];
    // 	const y1 = src1[ srcOffset1 + 1 ];
    // 	const z1 = src1[ srcOffset1 + 2 ];
    // 	const w1 = src1[ srcOffset1 + 3 ];

    // 	dst[ dstOffset ] = x0 * w1 + w0 * x1 + y0 * z1 - z0 * y1;
    // 	dst[ dstOffset + 1 ] = y0 * w1 + w0 * y1 + z0 * x1 - x0 * z1;
    // 	dst[ dstOffset + 2 ] = z0 * w1 + w0 * z1 + x0 * y1 - y0 * x1;
    // 	dst[ dstOffset + 3 ] = w0 * w1 - x0 * x1 - y0 * y1 - z0 * z1;

    // 	return dst;

    // }

    // T x() const { return this->x; }
    // void x(T value) {
    //     this->x = value;
    //     // TODO change callback
    // }
    // T y() const { return this->y; }
    // void y(T value) {
    //     this->y = value;
    //     // TODO change callback
    // }
    // T z() const { return this->z; }
    // void z(T value) {
    //     this->z = value;
    //     // TODO change callback
    // }
    // T w() const { return this->w; }
    // void w(T value) {
    //     this->w = value;
    //     // TODO change callback
    // }
    void set(T x, T y, T z, T w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
        // TODO change callback
    }
    type &operator=(const type &other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        this->w = other.w;
        return *this;
    }

    type &setFromEuler(const TEuler<T> &euler)// , bool update = true
    {
        auto x = euler.x, y = euler.y, z = euler.z;
        RotationOrder order = euler.order;
        // http://www.mathworks.com/matlabcentral/fileexchange/
        // 	20696-function-to-convert-between-dcm-euler-angles-quaternions-and-euler-vectors/
        //	content/SpinCalc.m
        auto cos = static_cast<T (*)(T)>(std::cos);
        auto sin = static_cast<T (*)(T)>(std::sin);

        auto c1 = cos(x / 2);
        auto c2 = cos(y / 2);
        auto c3 = cos(z / 2);

        auto s1 = sin(x / 2);
        auto s2 = sin(y / 2);
        auto s3 = sin(z / 2);

        switch (order)
        {
        case XYZ:
            this->x = s1 * c2 * c3 + c1 * s2 * s3;
            this->y = c1 * s2 * c3 - s1 * c2 * s3;
            this->z = c1 * c2 * s3 + s1 * s2 * c3;
            this->w = c1 * c2 * c3 - s1 * s2 * s3;
            break;

        case YXZ:
            this->x = s1 * c2 * c3 + c1 * s2 * s3;
            this->y = c1 * s2 * c3 - s1 * c2 * s3;
            this->z = c1 * c2 * s3 - s1 * s2 * c3;
            this->w = c1 * c2 * c3 + s1 * s2 * s3;
            break;

        case ZXY:
            this->x = s1 * c2 * c3 - c1 * s2 * s3;
            this->y = c1 * s2 * c3 + s1 * c2 * s3;
            this->z = c1 * c2 * s3 + s1 * s2 * c3;
            this->w = c1 * c2 * c3 - s1 * s2 * s3;
            break;

        case ZYX:
            this->x = s1 * c2 * c3 - c1 * s2 * s3;
            this->y = c1 * s2 * c3 + s1 * c2 * s3;
            this->z = c1 * c2 * s3 - s1 * s2 * c3;
            this->w = c1 * c2 * c3 + s1 * s2 * s3;
            break;

        case YZX:
            this->x = s1 * c2 * c3 + c1 * s2 * s3;
            this->y = c1 * s2 * c3 + s1 * c2 * s3;
            this->z = c1 * c2 * s3 - s1 * s2 * c3;
            this->w = c1 * c2 * c3 - s1 * s2 * s3;
            break;

        case XZY:
            this->x = s1 * c2 * c3 - c1 * s2 * s3;
            this->y = c1 * s2 * c3 - s1 * c2 * s3;
            this->z = c1 * c2 * s3 + s1 * s2 * c3;
            this->w = c1 * c2 * c3 + s1 * s2 * s3;
            break;

        default:
            // console.warn( 'CERAMICS.Quaternion: .setFromEuler() encountered
            // an unknown order: ' + order );
            break;
        }

        // TODO
        // if (update) this->_onChangeCallback();

        return *this;
    }

    type &setFromAxisAngle(const TVector<T, 3> &axis, T angle)
    {
        // http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/index.htm

        // assumes axis is normalized

        const auto halfAngle = angle / 2, s = std::sin(halfAngle);

        this->x = axis.x * s;
        this->y = axis.y * s;
        this->z = axis.z * s;
        this->w = std::cos(halfAngle);

        // this->_onChangeCallback();

        return *this;
    }

    type &setFromRotationMatrix(const TMatrix<T, 4, 4> &m)
    {
        // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm

        // assumes the upper 3x3 of m is a pure rotation matrix (i.e, unscaled)

        const auto &te = m.elements;

        auto
            m11 = te[0], m12 = te[1], m13 = te[2],
            m21 = te[4], m22 = te[5], m23 = te[6],
            m31 = te[8], m32 = te[9], m33 = te[10];

        auto trace = m11 + m22 + m33;

        if (trace > 0)
        {
            auto s = 0.5 / std::sqrt(trace + 1.0);

            this->w = 0.25 / s;
            this->x = (m32 - m23) * s;
            this->y = (m13 - m31) * s;
            this->z = (m21 - m12) * s;

        }
        else if (m11 > m22 && m11 > m33)
        {
            auto s = 2.0 * std::sqrt(1.0 + m11 - m22 - m33);

            this->w = (m32 - m23) / s;
            this->x = 0.25 * s;
            this->y = (m12 + m21) / s;
            this->z = (m13 + m31) / s;

        }
        else if (m22 > m33)
        {
            auto s = 2.0 * std::sqrt(1.0 + m22 - m11 - m33);

            this->w = (m13 - m31) / s;
            this->x = (m12 + m21) / s;
            this->y = 0.25 * s;
            this->z = (m23 + m32) / s;

        }
        else
        {
            auto s = 2.0 * std::sqrt(1.0 + m33 - m11 - m22);

            this->w = (m21 - m12) / s;
            this->x = (m13 + m31) / s;
            this->y = (m23 + m32) / s;
            this->z = 0.25 * s;
        }

        // this->_onChangeCallback();

        return *this;
    }

    type &setFromUnitVectors(const TVector<T, 3> &vFrom, TVector<T, 3> vTo)
    {
        // assumes direction vectors vFrom and vTo are normalized

        const auto EPS = 0.000001;

        T r = vFrom.dot(vTo) + 1;

        if (r < EPS)
        {
            r = T(0);

            if (std::abs(vFrom.x) > std::abs(vFrom.z))
            {
                this->x = -vFrom.y;
                this->y = vFrom.x;
                this->z = T(0);
                this->w = r;

            }
            else
            {
                this->x = T(0);
                this->y = -vFrom.z;
                this->z = vFrom.y;
                this->w = r;
            }

        }
        else
        {
            // crossVectors( vFrom, vTo ); // inlined to avoid cyclic dependency
            // on Vector3

            this->x = vFrom.y * vTo.z - vFrom.z * vTo.y;
            this->y = vFrom.z * vTo.x - vFrom.x * vTo.z;
            this->z = vFrom.x * vTo.y - vFrom.y * vTo.x;
            this->w = r;
        }

        return this->normalize();
    }

    T angleTo(const type &q)
    {
        return 2 *
            std::acos(std::abs(TMathUtils<T>::clamp(this->dot(q), -1, 1)));
    }

    type &rotateTowards(const type q, T step)
    {
        const auto angle = this->angleTo(q);

        if (angle == 0) return *this;

        const auto t = std::min(1, step / angle);

        this->slerp(q, t);

        return *this;
    }

    type &identity() { return this->set(T(0), T(0), T(0), T(1)); }

    type &inverse()
    {
        // quaternion is assumed to have unit length
        return this->conjugate();
    }

    type &conjugate()
    {
        this->x *= T(-1);
        this->y *= T(-1);
        this->z *= T(-1);
        // this->_onChangeCallback();
        return *this;
    }

    T dot(const type &v)
    {
        return this->x * v.x + this->y * v.y + this->z * v.z +
            this->w * v.w;
    }

    T lengthSq()
    {
        return this->x * this->x + this->y * this->y + this->z * this->z +
            this->w * this->w;
    }

    T length()
    {
        return std::sqrt(this->x * this->x + this->y * this->y +
                         this->z * this->z + this->w * this->w);
    }

    type &normalize()
    {
        T l = this->length();

        if (l == T(0))
        {
            this->x = T(0);
            this->y = T(0);
            this->z = T(0);
            this->w = T(1);

        }
        else
        {
            l = 1 / l;

            this->x *= l;
            this->y *= l;
            this->z *= l;
            this->w *= l;
        }

        // this->_onChangeCallback();

        return *this;
    }

    type &multiply(const type &q)
    {
        return this->multiplyQuaternions(*this, q);
    }

    type &multiply(const type &q, const type &p)
    {
        return this->multiplyQuaternions(q, p);
    }

    type &premultiply(const type &q)
    {
        return this->multiplyQuaternions(q, *this);
    }

    type &multiplyQuaternions(const type &a, const type &b)
    {
        // from
        // http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/code/index.htm

        const auto qax = a.x, qay = a.y, qaz = a.z, qaw = a.w;
        const auto qbx = b.x, qby = b.y, qbz = b.z, qbw = b.w;

        this->x = qax * qbw + qaw * qbx + qay * qbz - qaz * qby;
        this->y = qay * qbw + qaw * qby + qaz * qbx - qax * qbz;
        this->z = qaz * qbw + qaw * qbz + qax * qby - qay * qbx;
        this->w = qaw * qbw - qax * qbx - qay * qby - qaz * qbz;

        // this->_onChangeCallback();

        return *this;
    }

    type &slerp(const type &qb, T t)
    {
        if (t == 0) return *this;
        if (t == 1) return this->copy(qb);

        const auto x = this->x, y = this->y, z = this->z, w = this->w;

        // http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/

        auto cosHalfTheta = w * qb.w + x * qb.x + y * qb.y + z * qb.z;

        if (cosHalfTheta < 0)
        {
            this->w = -qb.w;
            this->x = -qb.x;
            this->y = -qb.y;
            this->z = -qb.z;

            cosHalfTheta = -cosHalfTheta;

        }
        else
        {
            this->copy(qb);
        }

        if (cosHalfTheta >= 1.0)
        {
            this->w = w;
            this->x = x;
            this->y = y;
            this->z = z;

            return *this;
        }

        const auto sqrSinHalfTheta = 1.0 - cosHalfTheta * cosHalfTheta;

        if (sqrSinHalfTheta <= std::numeric_limits<T>::epsilon())
        {
            const auto s = 1 - t;
            this->w = s * w + t * this->w;
            this->x = s * x + t * this->x;
            this->y = s * y + t * this->y;
            this->z = s * z + t * this->z;

            this->normalize();
            // this->_onChangeCallback();

            return *this;
        }

        const auto sinHalfTheta = std::sqrt(sqrSinHalfTheta);
        const auto halfTheta = std::atan2(sinHalfTheta, cosHalfTheta);
        const auto ratioA = std::sin((1 - t) * halfTheta) / sinHalfTheta,
            ratioB = std::sin(t * halfTheta) / sinHalfTheta;

        this->w = (w * ratioA + this->w * ratioB);
        this->x = (x * ratioA + this->x * ratioB);
        this->y = (y * ratioA + this->y * ratioB);
        this->z = (z * ratioA + this->z * ratioB);

        // this->_onChangeCallback();

        return *this;
    }

    bool equals(const type &quaternion)
    {
        return (quaternion.x == this->x) && (quaternion.y == this->y) &&
            (quaternion.z == this->z) && (quaternion.w == this->w);
    }


    // type &_onChange(callback_type callback) {
    //     this->_onChangeCallback = callback;
    //     return *this;
    // }

    T x = T(0);
    T y = T(0);
    T z = T(0);
    T w = T(1);
    // callback_type _onChangeCallback;
};
CERAMICS_NAMESPACE_END
