#pragma once
#include <algorithm>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

#include "../CeramicsMacro.h"
#include "ERotationOrder.h"
CERAMICS_NAMESPACE_BEGIN
std::ostringstream ss;

/* long _seed = 1234567; */
#define PI (3.14159265358979323846264338327950288)
template <class T>
class TMathUtils {
public:
    static T DEG2RAD;
    static T RAD2DEG;
    static T LN2;

    static std::string generateUUID() {
        static bool _lut_init = false;
        static std::string _lut[256];
        if (!_lut_init) {
            _lut_init = true;
            for (int i = 0; i < 256; ++i) {
                if (i < 16) {
                    _lut[i] = "0";
                } else {
                    ss << std::hex << i;
                    _lut[i] = ss.str();
                    ss.clear();
                }
            }
        }

        // http://stackoverflow.com/questions/105034/how-to-create-a-guid-uuid-in-javascript/21963136#21963136
        // */

        auto d0 = std::rand() * 0xffffffff | 0;
        auto d1 = std::rand() * 0xffffffff | 0;
        auto d2 = std::rand() * 0xffffffff | 0;
        auto d3 = std::rand() * 0xffffffff | 0;
        auto uuid = _lut[d0 & 0xff] + _lut[d0 >> 8 & 0xff] +
                    _lut[d0 >> 16 & 0xff] + _lut[d0 >> 24 & 0xff] + '-' +
                    _lut[d1 & 0xff] + _lut[d1 >> 8 & 0xff] + '-' +
                    _lut[d1 >> 16 & 0x0f | 0x40] + _lut[d1 >> 24 & 0xff] + '-' +
                    _lut[d2 & 0x3f | 0x80] + _lut[d2 >> 8 & 0xff] + '-' +
                    _lut[d2 >> 16 & 0xff] + _lut[d2 >> 24 & 0xff] +
                    _lut[d3 & 0xff] + _lut[d3 >> 8 & 0xff] +
                    _lut[d3 >> 16 & 0xff] + _lut[d3 >> 24 & 0xff];

        // .toUpperCase() here flattens concatenated strings to save heap memory
        // space. */ return uuid.toUpperCase();
        std::transform(uuid.begin(), uuid.end(),uuid.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        return uuid;
    }

    static T clamp(T value, T min, T max) {
        return std::max(min, std::min(max, value));
    }

    // compute euclidian modulo of m % n
    // https://en.wikipedia.org/wiki/Modulo_operation

    static T euclideanModulo(T n, T m) { return ((n % m) + m) % m; }

    // Linear mapping from range <a1, a2> to range <b1, b2>

    static T mapLinear(T x, T a1, T a2, T b1, T b2) {
        return b1 + (x - a1) * (b2 - b1) / (a2 - a1);
    }

    // https://en.wikipedia.org/wiki/Linear_interpolation

    static T lerp(T x, T y, T t) { return (1 - t) * x + t * y; }

    // http://en.wikipedia.org/wiki/Smoothstep

    static T smoothstep(T x, T min, T max) {
        if (x <= min) return 0;
        if (x >= max) return 1;

        x = (x - min) / (max - min);

        return x * x * (3 - 2 * x);
    }

    static T smootherstep(T x, T min, T max) {
        if (x <= min) return 0;
        if (x >= max) return 1;

        x = (x - min) / (max - min);

        return x * x * x * (x * (x * 6 - 15) + 10);
    }

    // Random integer from <low, high> interval

    static T randInt(T low, T high) {
        return low + std::floor(std::rand() * (high - low + 1));
    }

    // Random float from <low, high> interval

    static T randFloat(T low, T high) {
        return low + std::rand() * (high - low);
    }

    // Random float from <-range/2, range/2> interval

    static T randFloatSpread(T range) { return range * (0.5 - std::rand()); }

    // Deterministic pseudo-random float in the interval [ 0, 1 ]

    static int seededRandom(unsigned int s) {
        // if ( s !== undefined )
        int _seed = s % 2147483647;
        std::srand(_seed);

        // Park-Miller algorithm

        _seed = _seed * 16807 % 2147483647;

        return (_seed - 1) / 2147483646;
    }

    static T degToRad(T degrees) { return degrees * DEG2RAD; }

    static T radToDeg(T radians) { return radians * RAD2DEG; }

    static T isPowerOfTwo(T value) {
        return (value & (value - 1)) == 0 && value != 0;
    }

    static T ceilPowerOfTwo(T value) {
        return std::pow(2, std::ceil(std::log(value) / LN2));
    }

    static T floorPowerOfTwo(T value) {
        return std::pow(2, std::floor(std::log(value) / LN2));
    }

    static void setQuaternionFromProperEuler(T q, T a, T b, T c,
                                             RotationOrder order) {
        // Intrinsic Proper Euler Angles - see
        // https://en.wikipedia.org/wiki/Euler_angles

        // rotations are applied to the axes in the order specified by 'order'
        // rotation by angle 'a' is applied first, then by angle 'b', then by
        // angle 'c' angles are in radians

        const T c2 = std::cos(b / 2);
        const T s2 = std::sin(b / 2);

        const T c13 = std::cos((a + c) / 2);
        const T s13 = std::sin((a + c) / 2);

        const T c1_3 = std::cos((a - c) / 2);
        const T s1_3 = std::sin((a - c) / 2);

        const T c3_1 = std::cos((c - a) / 2);
        const T s3_1 = std::sin((c - a) / 2);

        switch (order) {
            case XYX:
                q.set(c2 * s13, s2 * c1_3, s2 * s1_3, c2 * c13);
                break;

            case YZY:
                q.set(s2 * s1_3, c2 * s13, s2 * c1_3, c2 * c13);
                break;

            case ZXZ:
                q.set(s2 * c1_3, s2 * s1_3, c2 * s13, c2 * c13);
                break;

            case XZX:
                q.set(c2 * s13, s2 * s3_1, s2 * c3_1, c2 * c13);
                break;

            case YXY:
                q.set(s2 * c3_1, c2 * s13, s2 * s3_1, c2 * c13);
                break;

            case ZYZ:
                q.set(s2 * s3_1, s2 * c3_1, c2 * s13, c2 * c13);
                break;

            default:
                break;
                // console.warn( 'CERAMICS.TMathUtils:
                // .setQuaternionFromProperEuler() encountered an unknown order:
                // ' + order );
        }
    }
};
template <class T>
T TMathUtils<T>::DEG2RAD = T(PI / 180);
template <class T>
T TMathUtils<T>::RAD2DEG = T(180 / PI);
template <class T>
T TMathUtils<T>::LN2 = std::log(T(2));
CERAMICS_NAMESPACE_END
