#pragma once
#include <cassert>
#include <cmath>
#include <initializer_list>

#include "../CeramicsMacro.h"
#include "ERotationOrder.h"
CERAMICS_NAMESPACE_BEGIN

template <class T, size_t dimension>
class TVector;

template <class T>
class TEuler;

template <class T>
class TQuaternion;

template <class T, size_t rowNum, size_t colNum>
struct TMatrix {
#define CERAMICS_DECLARE_MATRIX_COMMON_PART(rowNum, colNum)             \
    typedef T value_type;                                               \
    typedef TMatrix<T, rowNum, colNum> type;                            \
    typedef TMatrix<T, colNum, rowNum> transpose_type;                  \
    TMatrix(std::initializer_list<T> l) {                               \
        size_t i = 0;                                                   \
        for (auto it = l.begin(); it != l.end() && i < rowNum * colNum; \
             ++it, ++i) {                                               \
            elements[i] = *it;                                          \
        }                                                               \
        for (; i < rowNum * colNum; ++i) {                              \
            elements[i] = T(0);                                         \
        }                                                               \
    }                                                                   \
    TMatrix(const type &other) {                                        \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                this->elements[r * colNum + c] =                        \
                    other.elements[r * colNum + c];                     \
            }                                                           \
        }                                                               \
    }                                                                   \
    transpose_type transpose() const {                                  \
        transpose_type ret;                                             \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                ret[c * rowNum + r] = this->elements[r * colNum + c];   \
            }                                                           \
        }                                                               \
        return ret;                                                     \
    }                                                                   \
    T &operator[](size_t idx) {                                         \
        assert(idx < rowNum);                                           \
        return elements[idx];                                           \
    }                                                                   \
    type operator+(T s) const {                                         \
        type ret;                                                       \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                ret->elements[r * colNum + c] =                         \
                    this->elements[r * colNum + c] + s;                 \
            }                                                           \
        }                                                               \
        return ret;                                                     \
    }                                                                   \
    type &operator+=(T s) {                                             \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                this->elements[r * colNum + c] += s;                    \
            }                                                           \
        }                                                               \
        return *this;                                                   \
    }                                                                   \
    type operator-(T s) const {                                         \
        type ret;                                                       \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                ret->elements[r * colNum + c] =                         \
                    this->elements[r * colNum + c] - s;                 \
            }                                                           \
        }                                                               \
        return ret;                                                     \
    }                                                                   \
    type &operator-=(T s) {                                             \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                this->elements[r * colNum + c] -= s;                    \
            }                                                           \
        }                                                               \
        return *this;                                                   \
    }                                                                   \
    type operator*(T s) const {                                         \
        type ret;                                                       \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                ret->elements[r * colNum + c] =                         \
                    this->elements[r * colNum + c] * s;                 \
            }                                                           \
        }                                                               \
        return ret;                                                     \
    }                                                                   \
    type &operator*=(T s) {                                             \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                this->elements[r * colNum + c] *= s;                    \
            }                                                           \
        }                                                               \
        return *this;                                                   \
    }                                                                   \
    type operator/(T s) const {                                         \
        type ret;                                                       \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                ret->elements[r * colNum + c] =                         \
                    this->elements[r * colNum + c] / s;                 \
            }                                                           \
        }                                                               \
        return ret;                                                     \
    }                                                                   \
    type &operator/=(T s) {                                             \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                this->elements[r * colNum + c] /= s;                    \
            }                                                           \
        }                                                               \
        return *this;                                                   \
    }                                                                   \
    type operator+(const type &other) const {                           \
        type ret = *this;                                               \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                ret->elements[r * colNum + c] =                         \
                    this->elements[r * colNum + c] +                    \
                    other.elements[r * colNum + c];                     \
            }                                                           \
        }                                                               \
        return ret;                                                     \
    }                                                                   \
    type &operator+=(const type &other) {                               \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                this->elements[r * colNum + c] +=                       \
                    other.elements[r * colNum + c];                     \
            }                                                           \
        }                                                               \
        return *this;                                                   \
    }                                                                   \
    type operator-(const type &other) const {                           \
        type ret = *this;                                               \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                ret->elements[r * colNum + c] =                         \
                    this->elements[r * colNum + c] -                    \
                    other.elements[r * colNum + c];                     \
            }                                                           \
        }                                                               \
        return ret;                                                     \
    }                                                                   \
    type &operator-=(const type &other) {                               \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                this->elements[r * colNum + c] -=                       \
                    other.elements[r * colNum + c];                     \
            }                                                           \
        }                                                               \
        return *this;                                                   \
    }                                                                   \
    template <size_t colNum2>                                           \
    TMatrix<T, rowNum, colNum2> operator*(TMatrix<T, colNum, colNum2> &other) \
        const {                                                         \
        TMatrix<T, rowNum, colNum2> ret;                                \
        auto te = ret.elements;                                         \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum2; ++c) {                      \
                T sum = T(0);                                           \
                for (size_t i = 0; i < colNum; ++i) {                   \
                    sum += this->elements[r * colNum + i] *             \
                        other[i * colNum2 + c];                         \
                }                                                       \
                te[r * colNum + c] = sum;                               \
            }                                                           \
        }                                                               \
        return ret;                                                     \
    }                                                                   \
    type operator/(const type &other) const {                           \
        type ret = *this;                                               \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                ret[r * colNum + c] = this->elements[r * colNum + c] /  \
                    other.elements[r * colNum + c];                     \
            }                                                           \
        }                                                               \
        return ret;                                                     \
    }                                                                   \
    type &operator/=(const type &other) {                               \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                this->elements[r * colNum + c] /=                       \
                    other.elements[r * colNum + c];                     \
            }                                                           \
        }                                                               \
        return *this;                                                   \
    }                                                                   \
    type &operator=(const type &other) {                                \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                this->elements[r * colNum + c] =                        \
                    other.elements[r * colNum + c];                     \
            }                                                           \
        }                                                               \
        return *this;                                                   \
    }                                                                   \
    bool operator==(const type &other) const {                          \
        for (size_t r = 0; r < rowNum; ++r) {                           \
            for (size_t c = 0; c < colNum; ++c) {                       \
                if (this->elements[r * colNum + c] !=                   \
                    other.elements[r * colNum + c])                     \
                    return false;                                       \
            }                                                           \
        }                                                               \
        return true;                                                    \
    }                                                                   \
    type &copy(const type &other) {                                     \
        *this = other;                                                  \
        return *this;                                                   \
    }                                                                   \
    size_t row() const { return rowNum; }                               \
    size_t col() const { return colNum; }                               \
    bool operator!=(const type &other) const { return !(*this == other); } \
    static type makeZero() { return {0}; }                              \
    T elements[rowNum * colNum];                                        \

    CERAMICS_DECLARE_MATRIX_COMMON_PART(rowNum, colNum);

    TMatrix() {
        for (size_t r = 0; r < rowNum; ++r) {
            for (size_t c = 0; c < colNum; ++c) {
                elements[r * colNum + c] = T(0);
            }
        }
    }
};

// Squard Matrx
template <class T, size_t dimension>
struct TMatrix<T, dimension, dimension> {
    CERAMICS_DECLARE_MATRIX_COMMON_PART(dimension, dimension);
#define CERAMICS_DECLARE_SQUARD_MATRIX_COMMON_PART(dimension)   \
    TMatrix() {                                                 \
        this->identity();                                       \
    }                                                           \
    type &identity() {                                          \
        for (size_t r = 0; r < dimension; ++r) {                \
            for (size_t c = 0; c < dimension; ++c) {            \
                if (r == c)                                     \
                    elements[r * dimension + c] = T(1);         \
                else                                            \
                    elements[r * dimension + c] = T(0);         \
            }                                                   \
        }                                                       \
        return *this;                                           \
    }                                                           \
    type &operator*=(const type &other){                        \
        type result;                                            \
        auto te = result.elements;                              \
        for (size_t r = 0; r < dimension; ++r) {                \
            for (size_t c = 0; c < dimension; ++c) {            \
                T sum = T(0);                                   \
                for (size_t i = 0; i < dimension; ++i) {        \
                    sum += this->elements[r * dimension + i] *  \
                        other[i * dimension + c];               \
                }                                               \
                te[r * dimension + c] = sum;                    \
            }                                                   \
        }                                                       \
        copy(result);                                           \
        return *this;                                           \
    }                                                           \

    CERAMICS_DECLARE_SQUARD_MATRIX_COMMON_PART(dimension)

    T determinant() const { return calculateDeterminant(elements, dimension); }

    static T calculateDeterminant(const T *matrix, size_t n) {
        T det = T(0);
        if (n == 2)
            return ((matrix[0 * n + 0] * matrix[1 * n + 1]) -
                    (matrix[1 * n + 0] * matrix[0 * n + 1]));
        else {
            T *submatrix = new T[n * n];
            for (size_t x = 0; x < n; x++) {
                size_t subi = 0;
                for (size_t i = 1; i < n; i++) {
                    size_t subj = 0;
                    for (size_t j = 0; j < n; j++) {
                        if (j == x) continue;
                        submatrix[subi * n + subj] = matrix[i * n + j];
                        subj++;
                    }
                    subi++;
                }
                det = det + (std::pow(-1, x) * matrix[0 * n + x] *
                             calculateDeterminant(submatrix, n - 1));
            }
            delete[] submatrix;
        }
        return det;
    }
};
// Matrix3x3
template <class T>
struct TMatrix<T, 3, 3> {
    CERAMICS_DECLARE_MATRIX_COMMON_PART(3, 3)
    CERAMICS_DECLARE_SQUARD_MATRIX_COMMON_PART(3)
    type getInverse() const {
        auto me = this->elements;
        auto n11 = me[0], n21 = me[1], n31 = me[2], n12 = me[3], n22 = me[4],
            n32 = me[5], n13 = me[6], n23 = me[7], n33 = me[8],

            t11 = n33 * n22 - n32 * n23, t12 = n32 * n13 - n33 * n12,
            t13 = n23 * n12 - n22 * n13,

            det = n11 * t11 + n21 * t12 + n31 * t13;

        if (det == 0) return type::makeZero();
        type ret;
        auto te = ret.elements;

        const auto detInv = 1 / det;

        te[0] = t11 * detInv;
        te[1] = (n31 * n23 - n33 * n21) * detInv;
        te[2] = (n32 * n21 - n31 * n22) * detInv;

        te[3] = t12 * detInv;
        te[4] = (n33 * n11 - n31 * n13) * detInv;
        te[5] = (n31 * n12 - n32 * n11) * detInv;

        te[6] = t13 * detInv;
        te[7] = (n21 * n13 - n23 * n11) * detInv;
        te[8] = (n22 * n11 - n21 * n12) * detInv;

        return ret;
    }
    T determinant() const {
        const auto te = this->elements;

        const auto a = te[0], b = te[1], c = te[2], d = te[3], e = te[4],
            f = te[5], g = te[6], h = te[7], i = te[8];

        return a * e * i - a * f * h - b * d * i + b * f * g + c * d * h -
            c * e * g;
    }
    type &scale(T sx, T sy) {
        auto te = this->elements;

        te[0] *= sx;
        te[3] *= sx;
        te[6] *= sx;
        te[1] *= sy;
        te[4] *= sy;
        te[7] *= sy;

        return this;
    }
    type &rotate(T theta) {
        const auto c = std::cos(theta);
        const auto s = std::sin(theta);
        const auto te = this->elements;
        const auto a11 = te[0], a12 = te[3], a13 = te[6];
        const auto a21 = te[1], a22 = te[4], a23 = te[7];
        te[0] = c * a11 + s * a21;
        te[3] = c * a12 + s * a22;
        te[6] = c * a13 + s * a23;
        te[1] = -s * a11 + c * a21;
        te[4] = -s * a12 + c * a22;
        te[7] = -s * a13 + c * a23;
        return *this;
    }
    type &translate(T tx, T ty) {
        auto te = this->elements;

        te[0] += tx * te[2];
        te[3] += tx * te[5];
        te[6] += tx * te[8];
        te[1] += ty * te[2];
        te[4] += ty * te[5];
        te[7] += ty * te[8];

        return *this;
    }
    type &setFromMatrix4(const TMatrix<T, 4, 4> &m) {
        auto me = m.elements;

        *this = {

            me[0], me[4], me[8], me[1], me[5],
            me[9], me[2], me[6], me[10]

        };

        return *this;
    }
    type getNormalMatrix(const TMatrix<T, 4, 4> &matrix4) {
        return this->setFromMatrix4(matrix4).getInverse().transpose();
    }
};
template <class T>
struct TMatrix<T, 4, 4> {
    CERAMICS_DECLARE_MATRIX_COMMON_PART(4, 4)
    CERAMICS_DECLARE_SQUARD_MATRIX_COMMON_PART(4)
    type getInverse() const {
        auto me = this->elements;
        auto n11 = me[0], n21 = me[1], n31 = me[2], n41 = me[3], n12 = me[4],
            n22 = me[5], n32 = me[6], n42 = me[7], n13 = me[8], n23 = me[9],
            n33 = me[10], n43 = me[11], n14 = me[12], n24 = me[13],
            n34 = me[14], n44 = me[15],

            t11 = n23 * n34 * n42 - n24 * n33 * n42 + n24 * n32 * n43 -
            n22 * n34 * n43 - n23 * n32 * n44 + n22 * n33 * n44,
            t12 = n14 * n33 * n42 - n13 * n34 * n42 - n14 * n32 * n43 +
            n12 * n34 * n43 + n13 * n32 * n44 - n12 * n33 * n44,
            t13 = n13 * n24 * n42 - n14 * n23 * n42 + n14 * n22 * n43 -
            n12 * n24 * n43 - n13 * n22 * n44 + n12 * n23 * n44,
            t14 = n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 +
            n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34;

        auto det = n11 * t11 + n21 * t12 + n31 * t13 + n41 * t14;

        if (det == T(0)) return type::makeZero();

        type ret;
        auto te = ret.elements;

        auto detInv = 1 / det;

        te[0] = t11 * detInv;
        te[1] = (n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 +
                 n21 * n34 * n43 + n23 * n31 * n44 - n21 * n33 * n44) *
            detInv;
        te[2] = (n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 -
                 n21 * n34 * n42 - n22 * n31 * n44 + n21 * n32 * n44) *
            detInv;
        te[3] = (n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 +
                 n21 * n33 * n42 + n22 * n31 * n43 - n21 * n32 * n43) *
            detInv;

        te[4] = t12 * detInv;
        te[5] = (n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 -
                 n11 * n34 * n43 - n13 * n31 * n44 + n11 * n33 * n44) *
            detInv;
        te[6] = (n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 +
                 n11 * n34 * n42 + n12 * n31 * n44 - n11 * n32 * n44) *
            detInv;
        te[7] = (n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 -
                 n11 * n33 * n42 - n12 * n31 * n43 + n11 * n32 * n43) *
            detInv;

        te[8] = t13 * detInv;
        te[9] = (n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 +
                 n11 * n24 * n43 + n13 * n21 * n44 - n11 * n23 * n44) *
            detInv;
        te[10] = (n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42 -
                  n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44) *
            detInv;
        te[11] = (n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42 +
                  n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43) *
            detInv;

        te[12] = t14 * detInv;
        te[13] = (n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 -
                  n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34) *
            detInv;
        te[14] = (n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 +
                  n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34) *
            detInv;
        te[15] = (n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 -
                  n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33) *
            detInv;

        return ret;
    }
    type &scale(const TVector<T, 3> v) {
        auto te = this->elements;
        auto x = v.x, y = v.y, z = v.z;
        te[0] *= x;
        te[4] *= y;
        te[8] *= z;
        te[1] *= x;
        te[5] *= y;
        te[9] *= z;
        te[2] *= x;
        te[6] *= y;
        te[10] *= z;
        te[3] *= x;
        te[7] *= y;
        te[11] *= z;

        return *this;
    }

    type &compose(const TVector<T, 3> position, const TQuaternion<T> quaternion,
                  const TVector<T, 3> scale) {
        auto te = this->elements;

        auto x = quaternion.x, y = quaternion.y, z = quaternion.z,
            w = quaternion.w;
        auto x2 = x + x, y2 = y + y, z2 = z + z;
        auto xx = x * x2, xy = x * y2, xz = x * z2;
        auto yy = y * y2, yz = y * z2, zz = z * z2;
        auto wx = w * x2, wy = w * y2, wz = w * z2;
        auto sx = scale.x, sy = scale.y, sz = scale.z;

        te[0] = (1 - (yy + zz)) * sx;
        te[1] = (xy + wz) * sx;
        te[2] = (xz - wy) * sx;
        te[3] = 0;

        te[4] = (xy - wz) * sy;
        te[5] = (1 - (xx + zz)) * sy;
        te[6] = (yz + wx) * sy;
        te[7] = 0;

        te[8] = (xz + wy) * sz;
        te[9] = (yz - wx) * sz;
        te[10] = (1 - (xx + yy)) * sz;
        te[11] = 0;

        te[12] = position.x;
        te[13] = position.y;
        te[14] = position.z;
        te[15] = 1;

        return *this;
    }
    T determinant() const {
        auto te = this->elements;
        auto n11 = te[0], n12 = te[4], n13 = te[8], n14 = te[12];
        auto n21 = te[1], n22 = te[5], n23 = te[9], n24 = te[13];
        auto n31 = te[2], n32 = te[6], n33 = te[10], n34 = te[14];
        auto n41 = te[3], n42 = te[7], n43 = te[11], n44 = te[15];

        // TODO: make this more efficient
        //( based on
        // http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm
        //)

        return (n41 * (+n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 +
                       n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34) +
                n42 * (+n11 * n23 * n34 - n11 * n24 * n33 + n14 * n21 * n33 -
                       n13 * n21 * n34 + n13 * n24 * n31 - n14 * n23 * n31) +
                n43 * (+n11 * n24 * n32 - n11 * n22 * n34 - n14 * n21 * n32 +
                       n12 * n21 * n34 + n14 * n22 * n31 - n12 * n24 * n31) +
                n44 * (-n13 * n22 * n31 - n11 * n23 * n32 + n11 * n22 * n33 +
                       n13 * n21 * n32 - n12 * n21 * n33 + n12 * n23 * n31)

                );
    }

    type &decompose(TVector<T, 3> &position, TQuaternion<T> &quaternion,
                    TVector<T, 3> &scale) {
        auto te = this->elements;

        TVector<T, 3> _v1;
        auto sx = _v1.set(te[0], te[1], te[2]).length();
        auto sy = _v1.set(te[4], te[5], te[6]).length();
        auto sz = _v1.set(te[8], te[9], te[10]).length();

        // if determine is negative, we need to invert one scale
        auto det = this->determinant();
        if (det < 0) sx = -sx;

        position.x = te[12];
        position.y = te[13];
        position.z = te[14];

        // scale the rotation part
        TMatrix<T, 4, 4> _m1;
        _m1 = *this;

        auto invSX = 1 / sx;
        auto invSY = 1 / sy;
        auto invSZ = 1 / sz;

        _m1.elements[0] *= invSX;
        _m1.elements[1] *= invSX;
        _m1.elements[2] *= invSX;

        _m1.elements[4] *= invSY;
        _m1.elements[5] *= invSY;
        _m1.elements[6] *= invSY;

        _m1.elements[8] *= invSZ;
        _m1.elements[9] *= invSZ;
        _m1.elements[10] *= invSZ;

        quaternion.setFromRotationMatrix(_m1);

        scale.x = sx;
        scale.y = sy;
        scale.z = sz;

        return *this;
    }
    type &multiply(const type &m) { return this->multiplyMatrices(*this, m); }
    type &multiply(const type &m, const type &n) {
        return this->multiplyMatrices(m, n);
    }
    type &premultiply(const type &m) {
        return this->multiplyMatrices(m, *this);
    }
    type &multiplyMatrices(const type &a, const type &b) {
        auto ae = a.elements;
        auto be = b.elements;
        auto te = this->elements;

        auto a11 = ae[0], a12 = ae[4], a13 = ae[8], a14 = ae[12];
        auto a21 = ae[1], a22 = ae[5], a23 = ae[9], a24 = ae[13];
        auto a31 = ae[2], a32 = ae[6], a33 = ae[10], a34 = ae[14];
        auto a41 = ae[3], a42 = ae[7], a43 = ae[11], a44 = ae[15];

        auto b11 = be[0], b12 = be[4], b13 = be[8], b14 = be[12];
        auto b21 = be[1], b22 = be[5], b23 = be[9], b24 = be[13];
        auto b31 = be[2], b32 = be[6], b33 = be[10], b34 = be[14];
        auto b41 = be[3], b42 = be[7], b43 = be[11], b44 = be[15];

        te[0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
        te[4] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
        te[8] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
        te[12] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

        te[1] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
        te[5] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
        te[9] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
        te[13] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

        te[2] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
        te[6] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
        te[10] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
        te[14] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

        te[3] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
        te[7] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
        te[11] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
        te[15] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;

        return *this;
    }
    type &lookAt(const TVector<T, 3> &eye, const TVector<T, 3> &target,
                 const TVector<T, 3> &up) {
        const auto te = this->elements;
        TVector<T, 3> _x, _y, _z;
        _z.subVectors(eye, target);

        if (_z.lengthSq() == 0) {
            // eye and target are in the same position

            _z.z = 1;
        }

        _z.normalize();
        _x.crossVectors(up, _z);

        if (_x.lengthSq() == 0) {
            // up and z are parallel

            if (std::abs(up.z) == 1) {
                _z.x += 0.0001;

            } else {
                _z.z += 0.0001;
            }

            _z.normalize();
            _x.crossVectors(up, _z);
        }

        _x.normalize();
        _y.crossVectors(_z, _x);

        te[0] = _x.x;
        te[4] = _y.x;
        te[8] = _z.x;
        te[1] = _x.y;
        te[5] = _y.y;
        te[9] = _z.y;
        te[2] = _x.z;
        te[6] = _y.z;
        te[10] = _z.z;
        return *this;
    }
    type &extractRotation(const type &m) {
        // this method does not support reflection matrices

        TVector<T, 3> _v1;
        auto te = this->elements;
        auto me = m.elements;

        auto scaleX = 1 / _v1.setFromMatrixColumn(m, 0).length();
        auto scaleY = 1 / _v1.setFromMatrixColumn(m, 1).length();
        auto scaleZ = 1 / _v1.setFromMatrixColumn(m, 2).length();

        te[0] = me[0] * scaleX;
        te[1] = me[1] * scaleX;
        te[2] = me[2] * scaleX;
        te[3] = 0;

        te[4] = me[4] * scaleY;
        te[5] = me[5] * scaleY;
        te[6] = me[6] * scaleY;
        te[7] = 0;

        te[8] = me[8] * scaleZ;
        te[9] = me[9] * scaleZ;
        te[10] = me[10] * scaleZ;
        te[11] = 0;

        te[12] = 0;
        te[13] = 0;
        te[14] = 0;
        te[15] = 1;

        return *this;
    }
    static type makeTranslation(T x, T y, T z) {
        return {

            1, 0, 0, x, 0, 1, 0, y, 0,
            0, 1, z, 0, 0, 0, 1

        };
    }
    static type makeRotationX(T theta) {
        type ret;
        auto c = cos(theta), s = sin(theta);
        ret={1, 0, 0, 0, 0, c, -s, 0, 0, s, c, 0, 0, 0, 0, 1};
        return ret;
    }

    static type makeRotationY(T theta) {
        type ret;
        auto c = cos(theta), s = sin(theta);
        ret={c, 0, s, 0, 0, 1, 0, 0, -s, 0, c, 0, 0, 0, 0, 1};
        return ret;
    }
    static type makeRotationZ(T theta) {
        type ret;
        auto c = cos(theta), s = sin(theta);
        ret={c, -s, 0, 0, s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
        return ret;
    }
    static type makeRotationAxis(TVector<T, 3> axis, T angle) {
        type ret;
        auto c = cos(angle);
        auto s = sin(angle);
        auto t = 1 - c;
        auto x = axis.x, y = axis.y, z = axis.z;
        auto tx = t * x, ty = t * y;
        ret={tx * x + c, tx * y - s * z, tx * z + s * y, 0, tx * y + s * z,
            ty * y + c, ty * z - s * x, 0, tx * z - s * y, ty * z + s * x,
            t * z * z + c, 0, 0, 0, 0, 1};
        return ret;
    }
    static type makeScale(T x, T y, T z) {
        return {x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1};
    }
    static type makeShear(T x, T y, T z) {
        return {1, y, z, 0, x, 1, z, 0, x, y, 1, 0, 0, 0, 0, 1};
    }
    static type makePerspective(T left, T right, T top, T bottom, T near,
                                T far) {
        type ret;
        auto te = ret.elements;
        auto x = 2 * near / (right - left);
        auto y = 2 * near / (top - bottom);

        auto a = (right + left) / (right - left);
        auto b = (top + bottom) / (top - bottom);
        auto c = -(far + near) / (far - near);
        auto d = -2 * far * near / (far - near);

        te[0] = x;
        te[4] = 0;
        te[8] = a;
        te[12] = 0;
        te[1] = 0;
        te[5] = y;
        te[9] = b;
        te[13] = 0;
        te[2] = 0;
        te[6] = 0;
        te[10] = c;
        te[14] = d;
        te[3] = 0;
        te[7] = 0;
        te[11] = -1;
        te[15] = 0;

        return ret;
    }

    static type makeOrthographic(T left, T right, T top, T bottom, T near,
                                 T far) {
        type ret;
        auto te = ret.elements;
        auto w = 1.0 / (right - left);
        auto h = 1.0 / (top - bottom);
        auto p = 1.0 / (far - near);

        auto x = (right + left) * w;
        auto y = (top + bottom) * h;
        auto z = (far + near) * p;

        te[0] = 2 * w;
        te[4] = 0;
        te[8] = 0;
        te[12] = -x;
        te[1] = 0;
        te[5] = 2 * h;
        te[9] = 0;
        te[13] = -y;
        te[2] = 0;
        te[6] = 0;
        te[10] = -2 * p;
        te[14] = -z;
        te[3] = 0;
        te[7] = 0;
        te[11] = 0;
        te[15] = 1;
        return ret;
    }
    static type makeRotationFromEuler(const TEuler<T> &euler) {
        type ret;
        auto te = ret.elements;
        auto x = euler.x, y = euler.y, z = euler.z;
        auto a = std::cos(x), b = std::sin(x);
        auto c = std::cos(y), d = std::sin(y);
        auto e = std::cos(z), f = std::sin(z);

        if (euler.order == RotationOrder::XYZ) {
            auto ae = a * e, af = a * f, be = b * e, bf = b * f;

            te[0] = c * e;
            te[4] = -c * f;
            te[8] = d;

            te[1] = af + be * d;
            te[5] = ae - bf * d;
            te[9] = -b * c;

            te[2] = bf - ae * d;
            te[6] = be + af * d;
            te[10] = a * c;

        } else if (euler.order == RotationOrder::YXZ) {
            auto ce = c * e, cf = c * f, de = d * e, df = d * f;

            te[0] = ce + df * b;
            te[4] = de * b - cf;
            te[8] = a * d;

            te[1] = a * f;
            te[5] = a * e;
            te[9] = -b;

            te[2] = cf * b - de;
            te[6] = df + ce * b;
            te[10] = a * c;

        } else if (euler.order == RotationOrder::ZXY) {
            auto ce = c * e, cf = c * f, de = d * e, df = d * f;

            te[0] = ce - df * b;
            te[4] = -a * f;
            te[8] = de + cf * b;

            te[1] = cf + de * b;
            te[5] = a * e;
            te[9] = df - ce * b;

            te[2] = -a * d;
            te[6] = b;
            te[10] = a * c;

        } else if (euler.order == RotationOrder::ZYX) {
            auto ae = a * e, af = a * f, be = b * e, bf = b * f;

            te[0] = c * e;
            te[4] = be * d - af;
            te[8] = ae * d + bf;

            te[1] = c * f;
            te[5] = bf * d + ae;
            te[9] = af * d - be;

            te[2] = -d;
            te[6] = b * c;
            te[10] = a * c;

        } else if (euler.order == RotationOrder::YZX) {
            auto ac = a * c, ad = a * d, bc = b * c, bd = b * d;

            te[0] = c * e;
            te[4] = bd - ac * f;
            te[8] = bc * f + ad;

            te[1] = f;
            te[5] = a * e;
            te[9] = -b * e;

            te[2] = -d * e;
            te[6] = ad * f + bc;
            te[10] = ac - bd * f;

        } else if (euler.order == RotationOrder::XZY) {
            auto ac = a * c, ad = a * d, bc = b * c, bd = b * d;

            te[0] = c * e;
            te[4] = -f;
            te[8] = d * e;

            te[1] = ac * f + bd;
            te[5] = a * e;
            te[9] = ad * f - bc;

            te[2] = bc * f - ad;
            te[6] = b * e;
            te[10] = bd * f + ac;
        }

        // bottom row
        te[3] = 0;
        te[7] = 0;
        te[11] = 0;

        // last column
        te[12] = 0;
        te[13] = 0;
        te[14] = 0;
        te[15] = 1;

        return ret;
    }

    static type makeRotationFromQuaternion(const TQuaternion<T> q) {
        type ret;
        return ret.compose(TVector<T, 3>::zero(), q, TVector<T, 3>::one());
    }
};
#undef CERAMICS_DECLARE_MATRIX_COMMON_PART
#undef CERAMICS_DECLARE_SQUARD_MATRIX_COMMON_PART
CERAMICS_NAMESPACE_END
