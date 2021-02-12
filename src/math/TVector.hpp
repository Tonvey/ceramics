#pragma once
#include <array>
#include <cassert>
#include <cmath>
#include <initializer_list>
#include "../CeramicsMacro.h"
CERAMICS_NAMESPACE_BEGIN
template <class T>
class TEuler;

template <class T>
class TQuaternion;

template <class T, size_t d1, size_t d2>
class TMatrix;

template <class T, size_t d>
static void TFuncArraySet(std::array<T, d> &arr, T val) {
    for (size_t i = 0; i < d; ++i) {
        arr[i] = val;
    }
}
template <class T>
static void TFuncArraySet(T arr[], size_t size, T val) {
    for (size_t i = 0; i < size; ++i) {
        arr[i] = val;
    }
}
template <class T, size_t d>
static void TFuncArrayNegate(std::array<T, d> &arr) {
    for (size_t i = 0; i < d; ++i) {
        arr[i] = -arr[i];
    }
}
template <class T>
static void TFuncArrayNegate(T arr[], size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr[i] = -arr[i];
    }
}
template <class T, size_t d>
static void TFuncArrayAdd(std::array<T, d> &arr1,
                          const std::array<T, d> &arr2) {
    for (size_t i = 0; i < d; ++i) {
        arr1[i] += arr2[i];
    }
}
template <class T>
static void TFuncArrayAdd(T arr1[], const T arr2[], size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr1[i] += arr2[i];
    }
}
template <class T, size_t d>
static void TFuncArraySub(std::array<T, d> &arr1,
                          const std::array<T, d> &arr2) {
    for (size_t i = 0; i < d; ++i) {
        arr1[i] -= arr2[i];
    }
}
template <class T>
static void TFuncArraySub(T arr1[], const T arr2[], size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr1[i] -= arr2[i];
    }
}
template <class T, size_t d>
static void TFuncArrayMultiply(std::array<T, d> &arr1,
                               const std::array<T, d> &arr2) {
    for (size_t i = 0; i < d; ++i) {
        arr1[i] *= arr2[i];
    }
}
template <class T>
static void TFuncArrayMultiply(T arr1[], const T arr2[], size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr1[i] *= arr2[i];
    }
}
template <class T, size_t d>
static void TFuncArrayDivide(std::array<T, d> &arr1,
                             const std::array<T, d> &arr2) {
    for (size_t i = 0; i < d; ++i) {
        arr1[i] /= arr2[i];
    }
}
template <class T>
static void TFuncArrayDivide(T arr1[], const T arr2[], size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr1[i] /= arr2[i];
    }
}
template <class T, size_t d>
static void TFuncArrayAddScalar(std::array<T, d> &arr1,
                                T scalar) {
    for (size_t i = 0; i < d; ++i) {
        arr1[i] += scalar;
    }
}
template <class T>
static void TFuncArrayAddScalar(T arr1[], const T scalar, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr1[i] += scalar;
    }
}
template <class T, size_t d>
static void TFuncArraySubScalar(std::array<T, d> &arr1, T scalar) {
    for (size_t i = 0; i < d; ++i) {
        arr1[i] -= scalar;
    }
}
template <class T>
static void TFuncArraySubScalar(T arr1[], const T scalar, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr1[i] -= scalar;
    }
}
template <class T, size_t d>
static void TFuncArrayMultiplyScalar(std::array<T, d> &arr1, T scalar) {
    for (size_t i = 0; i < d; ++i) {
        arr1[i] *= scalar;
    }
}
template <class T>
static void TFuncArrayMultiplyScalar(T arr1[], T scalar, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr1[i] *= scalar;
    }
}
template <class T, size_t d>
static void TFuncArrayDivideScalar(std::array<T, d> &arr1, T scalar) {
    for (size_t i = 0; i < d; ++i) {
        arr1[i] /= scalar;
    }
}
template <class T>
static void TFuncArrayDivideScalar(T arr1[], T scalar, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr1[i] /= scalar;
    }
}

// TVectorBase
template <class T, size_t dimension>
class TVector {
    // TVector CommonPart
#define CERAMICS_DECLARE_VECTOR_COMMON_PART(dimension)                        \
public:                                                                    \
    typedef TVector<T, dimension> type;                                    \
    typedef const TVector<T, dimension> const_type;                        \
    typedef std::array<T, dimension> array_t;                              \
    TVector(std::initializer_list<T> l) {                                  \
        CERAMICS_LOG_TEST("TVector(std::initializer_list<T> l)\n");           \
        this->set(l);                                                      \
    }                                                                      \
    TVector(const_type &other) {                                           \
        CERAMICS_LOG_TEST("TVector(const_type &other)\n");                    \
        this->copy(other);                                                 \
    }                                                                      \
    ~TVector() { CERAMICS_LOG_TEST("~TVector()\n"); }                         \
    static type zero() { return type().setAll(T(0)); }                     \
    static type one() { return type().setAll(T(1)); }                      \
    const T &operator[](size_t idx) const {                                \
        assert(idx < dimension);                                           \
        return mArr[idx];                                                  \
    }                                                                      \
    T &operator[](size_t idx) {                                            \
        assert(idx < dimension);                                           \
        return mArr[idx];                                                  \
    }                                                                      \
    type operator+(T s) const {                                            \
        type ret;                                                          \
        TFuncArrayAddScalar(ret.mArr, s);                                  \
        return ret;                                                        \
    }                                                                      \
    type operator-(T s) const {                                            \
        type ret;                                                          \
        TFuncArraySubScalar(ret.mArr, s);                                  \
        return ret;                                                        \
    }                                                                      \
    type operator*(T s) const {                                            \
        type ret;                                                          \
        TFuncArrayMultiplyScalar(ret.mArr, s);                             \
        return ret;                                                        \
    }                                                                      \
    type operator/(T s) const {                                            \
        type ret;                                                          \
        TFuncArrayDivideScalar(ret.mArr, s);                               \
        return ret;                                                        \
    }                                                                      \
    type operator+(const_type &other) const {                              \
        type ret = *this;                                                  \
        TFuncArrayAdd(ret.mArr, other.mArr);                               \
        return ret;                                                        \
    }                                                                      \
    type operator-(const_type &other) const {                              \
        type ret = *this;                                                  \
        TFuncArraySub(ret.mArr, other.mArr);                               \
        return ret;                                                        \
    }                                                                      \
    type operator*(const_type &other) const {                              \
        type ret = *this;                                                  \
        TFuncArrayMultiply(ret.mArr, other.mArr, dimension);               \
        return ret;                                                        \
    }                                                                      \
    type operator/(const_type &other) const {                              \
        type ret = *this;                                                  \
        TFuncArrayDivide(ret.mArr, other.mArr, dimension);                 \
        return ret;                                                        \
    }                                                                      \
    type &operator=(const_type &other) { return this->copy(other); }       \
    type &operator=(std::initializer_list<T> l) {                          \
        this->set(l);                                                      \
        return *this;                                                      \
    }                                                                      \
    bool operator==(const_type &other) const {                             \
        for (size_t i = 0; i < dimension; ++i) {                           \
            if (this->mArr[i] != other.mArr[i]) return false;              \
        }                                                                  \
        return true;                                                       \
    }                                                                      \
    bool operator!=(const_type &other) const { return !(*this == other); } \
    size_t size() const { return dimension; }                              \
    type &copy(const_type &other) {                                        \
        for (size_t i = 0; i < dimension; ++i) {                           \
            this->mArr[i] = other.mArr[i];                                 \
        }                                                                  \
        return *this;                                                      \
    }                                                                      \
    type &setAll(T value) {                                                \
        for (auto &i : this->mArr) {                                       \
            i = value;                                                     \
        }                                                                  \
        return *this;                                                      \
    }                                                                      \
    type &add(const_type &other) {                                         \
        TFuncArrayAdd(this->mArr, other.mArr);                             \
        return *this;                                                      \
    }                                                                      \
    type &addScalar(T s) {                                                 \
        TFuncArrayAddScalar(this->mArr, s);                                \
        return *this;                                                      \
    }                                                                      \
    type &sub(const_type &other) {                                         \
        TFuncArraySub(this->mArr, other.mArr);                             \
        return *this;                                                      \
    }                                                                      \
    type &subScalar(T s) {                                                 \
        TFuncArraySubScalar(this->mArr, s);                                \
        return *this;                                                      \
    }                                                                      \
    type &subVectors(const_type &v1, const_type &v2) {                     \
        *this = v1 - v2;                                                   \
        return *this;                                                      \
    }                                                                      \
    type &multiply(const_type &other) {                                    \
        TFuncArrayMultiply(this->mArr, other.mArr);                        \
        return *this;                                                      \
    }                                                                      \
    type &multiplyScalar(T s) {                                            \
        TFuncArrayMultiplyScalar(this->mArr, s);                           \
        return *this;                                                      \
    }                                                                      \
    type &divide(const_type &other) {                                      \
        TFuncArrayDivide(this->mArr, other.mArr);                          \
        return *this;                                                      \
    }                                                                      \
    type &divideScalar(T s) {                                              \
        TFuncArrayDivideScalar(this->mArr, s);                             \
        return *this;                                                      \
    }                                                                      \
    type &min(const_type &other) {                                         \
        for (size_t i = 0; i < dimension; ++i) {                           \
            this->mArr[i] = std::min(this->mArr[i], other.mArr[i]);        \
        }                                                                  \
        return *this;                                                      \
    }                                                                      \
    type &max(const_type &other) {                                         \
        for (size_t i = 0; i < dimension; ++i) {                           \
            this->mArr[i] = std::max(this->mArr[i], other.mArr[i]);        \
        }                                                                  \
        return *this;                                                      \
    }                                                                      \
    T dot(const_type &other) const {                                       \
        T sum = T(0);                                                      \
        for (size_t i = 0; i < dimension; ++i) {                           \
            sum += (*this)[i] * other.mArr[i];                             \
        }                                                                  \
        return sum;                                                        \
    }                                                                      \
    type &negate() {                                                       \
        TFuncArrayNegate(this->mArr);                                      \
        return *this;                                                      \
    }                                                                      \
    T length() const {                                                     \
        T sum = T(0);                                                      \
        for (size_t i = 0; i < dimension; ++i) {                           \
            sum += mArr[i] * mArr[i];                                      \
        }                                                                  \
        return std::sqrt(sum);                                             \
    }                                                                      \
    T lengthSq() {                                                         \
        T sum = T(0);                                                      \
        for (auto &i : mArr) {                                             \
            sum += i;                                                      \
        }                                                                  \
        return sum;                                                        \
    }                                                                      \
    T manhattanLength() {                                                  \
        T sum = T(0);                                                      \
        for (size_t i = 0; i < dimension; ++i) {                           \
            sum += std::abs(mArr[i]);                                      \
        }                                                                  \
        return sum;                                                        \
    }                                                                      \
    type &clamp(const_type &min, const_type &max) {                        \
        for (size_t i = 0; i < dimension; ++i) {                           \
            mArr[i] = std::max(min[i], std::min(max[i], mArr[i]));         \
        }                                                                  \
        return *this;                                                      \
    }                                                                      \
    type &normalize() {                                                    \
        T length = this->length();                                         \
        return this->divideScalar(length == T(0) ? T(1) : length);         \
    }                                                                      \
    type clone() const { return *this; }                                   \
                                                                           \
private:                                                                   \
    array_t mArr;

public:
    TVector() {
        CERAMICS_LOG_TEST("TVector()\n");
        TFuncArraySet(this->mArr, T(0));
    }
    CERAMICS_DECLARE_VECTOR_COMMON_PART(dimension)
};

// TVector2
template <class T>
class TVector<T, 2> {
    CERAMICS_DECLARE_VECTOR_COMMON_PART(2)
public:
    TVector(const T x = T(0), const T y = T(0)) { this->set(x, y); }
    type &set(const T x = T(0), const T y = T(0)) {
        this->x = x;
        this->y = y;
        return *this;
    }
    T cross(const_type &other) { return this->x * other.y - this->y * other.x; }
    T &x = mArr[0];
    T &y = mArr[1];
    type &applyMatrix3(const TMatrix<T,3,3> &m ) {
        const auto x = this->x;
        const auto y = this->y;
        const auto &e = m.elements;
		this->x = e[ 0 ] * x + e[ 3 ] * y + e[ 6 ];
		this->y = e[ 1 ] * x + e[ 4 ] * y + e[ 7 ];
		return *this;
	}
};

// TVector3
template <class T>
class TVector<T, 3> {
    CERAMICS_DECLARE_VECTOR_COMMON_PART(3)
public:
    TVector(const T x = T(0), const T y = T(0), const T z = T(0)) {
        this->set(x, y, z);
    }
    T &x = mArr[0];
    T &y = mArr[1];
    T &z = mArr[2];
    type &set(const T x = T(0), const T y = T(0), const T z = T(0)) {
        this->x = x;
        this->y = y;
        this->z = z;
        return *this;
    }
    type &cross(const_type &other) {
        T ax = this->x, ay = this->y, az = this->z;
        T bx = other.x, by = other.y, bz = other.z;

        x = ay * bz - az * by;
        y = az * bx - ax * bz;
        z = ax * by - ay * bx;
        return *this;
    }
    type &crossVectors(const_type &a, const_type &b) {
        const auto ax = a.x, ay = a.y, az = a.z;
        const auto bx = b.x, by = b.y, bz = b.z;

        x = ay * bz - az * by;
        y = az * bx - ax * bz;
        z = ax * by - ay * bx;

        return *this;
    }

	type &applyMatrix3(const TMatrix<T,3,3> &m ) {

		auto x = this->x, y = this->y, z = this->z;
		auto e = m.elements;

		this->x = e[ 0 ] * x + e[ 3 ] * y + e[ 6 ] * z;
		this->y = e[ 1 ] * x + e[ 4 ] * y + e[ 7 ] * z;
		this->z = e[ 2 ] * x + e[ 5 ] * y + e[ 8 ] * z;

		return *this;

	}
    type &applyMatrix4(const TMatrix<T, 4, 4> &m) {
        auto x = this->x, y = this->y, z = this->z;
        auto e = m.elements;

        auto w = 1 / (e[3] * x + e[7] * y + e[11] * z + e[15]);

        this->x = (e[0] * x + e[4] * y + e[8] * z + e[12]) * w;
        this->y = (e[1] * x + e[5] * y + e[9] * z + e[13]) * w;
        this->z = (e[2] * x + e[6] * y + e[10] * z + e[14]) * w;

        return *this;
    }
    type &applyNormalMatrix(const TMatrix<T, 3, 3> &m) {
        return this->applyMatrix3( m ).normalize();
    }

    type &applyQuaternion(const TQuaternion<T> &q) {
        const auto x = this->x, y = this->y, z = this->z;
        const auto qx = q.x, qy = q.y, qz = q.z, qw = q.w;

        // calculate quat * vector

        const auto ix = qw * x + qy * z - qz * y;
        const auto iy = qw * y + qz * x - qx * z;
        const auto iz = qw * z + qx * y - qy * x;
        const auto iw = -qx * x - qy * y - qz * z;

        // calculate result * inverse quat

        this->x = ix * qw + iw * -qx + iy * -qz - iz * -qy;
        this->y = iy * qw + iw * -qy + iz * -qx - ix * -qz;
        this->z = iz * qw + iw * -qz + ix * -qy - iy * -qx;

        return *this;
    }
	type &transformDirection(const TMatrix<T,4,4> &m ) {

		const auto x = this->x, y = this->y, z = this->z;
		const auto &e = m->elements;

		this->x = e[ 0 ] * x + e[ 4 ] * y + e[ 8 ] * z;
		this->y = e[ 1 ] * x + e[ 5 ] * y + e[ 9 ] * z;
		this->z = e[ 2 ] * x + e[ 6 ] * y + e[ 10 ] * z;

		return this->normalize();

	}
    type &setFromMatrixPosition(const TMatrix<T, 4, 4> &m) {
        const auto e = m.elements;

        this->x = e[12];
        this->y = e[13];
        this->z = e[14];

        return *this;
    }

    type &setFromMatrixScale(const TMatrix<T, 4, 4> &m) {
        const auto sx = this->setFromMatrixColumn(m, 0).length();
        const auto sy = this->setFromMatrixColumn(m, 1).length();
        const auto sz = this->setFromMatrixColumn(m, 2).length();

        this->x(sx);
        this->y(sy);
        this->z(sz);

        return *this;
    }

    type &setFromMatrixColumn(const TMatrix<T, 4, 4> &m, int index) {
        return this->fromArray(m.elements, index * 4);
    }

    type &setFromMatrix3Column(const TMatrix<T, 3, 3> &m, int index) {
        return this->fromArray(m.elements, index * 3);
    }

    type &fromArray(const T *array, int offset = 0) {
        this->x = array[offset + 0];
        this->y = array[offset + 1];
        this->z = array[offset + 2];

        return *this;
    }
    T distanceToSquared(const_type &v){
        auto dx = this->x - v.x, dy = this->y - v.y, dz = this->z - v.z;
		return dx * dx + dy * dy + dz * dz;    
    }
};

// TVector4
template <class T>
class TVector<T, 4> {
    CERAMICS_DECLARE_VECTOR_COMMON_PART(4)
public:
    TVector(const T x = T(0), const T y = T(0), const T z = T(0),
            const T w = T(0)) {
        this->set(x, y, z, w);
    }
    type &set(const T x = T(0), const T y = T(0), const T z = T(0),
              const T w = T(0)) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
        return *this;
    }
    T &x = mArr[0];
    T &y = mArr[1];
    T &z = mArr[2];
    T &w = mArr[3];
};

#undef CERAMICS_DECLARE_VECTOR_COMMON_PART
CERAMICS_NAMESPACE_END
