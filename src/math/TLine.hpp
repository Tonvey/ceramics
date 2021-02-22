#pragma once
#include "TMathUtils.hpp"
#include "../CeramicsPrerequisites.h"
CERAMICS_NAMESPACE_BEGIN
#define CERAMICS_DECLARE_LINE_COMMON_PART(dimension)                    \
    typedef T value_type;                                               \
    typedef TLine<T, dimension> type;                                   \
    typedef TVector<T, dimension> vec_t;                                \
    vec_t start;                                                        \
    vec_t end;                                                          \
    TLine(const vec_t &start = vec_t(), const vec_t &end = vec_t())     \
        : start(start), end(end) {}                                     \
    type &set(const vec_t &start, const vec_t &end)                     \
    {                                                                   \
        this->start.copy(start);                                        \
        this->end.copy(end);                                            \
        return *this;                                                   \
    }                                                                   \
    type clone() { return *this; }                                      \
    type &operator=(const type &line) { return this->copy(line); }      \
    type &copy(const type &line)                                        \
    {                                                                   \
        this->start.copy(line.start);                                   \
        this->end.copy(line.end);                                       \
        return *this;                                                   \
    }                                                                   \
    vec_t getCenter()                                                   \
    {                                                                   \
        vec_t target;                                                   \
        return this->getCenter(target);                                 \
    }                                                                   \
    vec_t &getCenter(vec_t &target)                                     \
    {                                                                   \
        return target.addVectors(this->start, this->end).multiplyScalar(0.5); \
    }                                                                   \
    vec_t delta()                                                       \
    {                                                                   \
        vec_t target;                                                   \
        return this->delta(target);                                     \
    }                                                                   \
    vec_t &delta(vec_t &target)                                         \
    {                                                                   \
        return target.subVectors(this->end, this->start);               \
    }                                                                   \
    T distanceSq() { return this->start.distanceToSquared(this->end); } \
    T distance() { return this->start.distanceTo(this->end); }          \
    vec_t at(T t)                                                       \
    {                                                                   \
        vec_t target;                                                   \
        return this->at(t, target);                                     \
    }                                                                   \
    vec_t &at(T t, vec_t &target)                                       \
    {                                                                   \
        return this->delta(target).multiplyScalar(t).add(this->start);  \
    }                                                                   \
    T closestPointToPointParameter(const vec_t &point, bool clampToLine) \
    {                                                                   \
        vec_t _startP, _startEnd;                                       \
        _startP.subVectors(point, this->start);                         \
        _startEnd.subVectors(this->end, this->start);                   \
        auto startEnd2 = _startEnd.dot(_startEnd);                      \
        auto startEnd_startP = _startEnd.dot(_startP);                  \
        auto t = startEnd_startP / startEnd2;                           \
        if (clampToLine)                                                \
        {                                                               \
            t = TMathUtils<T>::clamp(t, 0, 1);                          \
        }                                                               \
        return t;                                                       \
    }                                                                   \
    vec_t closestPointToPoint(const vec_t &point, bool clampToLine)     \
    {                                                                   \
        vec_t target;                                                   \
        return this->closestPointToPoint(point, clampToLine, target);   \
    }                                                                   \
    vec_t &closestPointToPoint(const vec_t &point, bool clampToLine,    \
                               vec_t &target)                           \
    {                                                                   \
        auto t = this->closestPointToPointParameter(point, clampToLine); \
        return this->delta(target).multiplyScalar(t).add(this->start);  \
    }                                                                   \
    bool operator==(const type &line) { return this->equals(line); }    \
    bool equals(const type &line)                                       \
    {                                                                   \
        return line.start.equals(this->start) && line.end.equals(this->end); \
    }
template <class T, size_t dimension>
struct TLine
{
    CERAMICS_DECLARE_LINE_COMMON_PART(dimension);
};

template <class T>
struct TLine<T, 3>
{
    CERAMICS_DECLARE_LINE_COMMON_PART(3);
    typedef TMatrix<T, 4, 4> matrix4_t;
    type &applyMatrix4(const matrix4_t &matrix)
    {
        this->start.applyMatrix4(matrix);
        this->end.applyMatrix4(matrix);
        return *this;
    }
};

#undef CERAMICS_DECLARE_LINE_COMMON_PART
CERAMICS_NAMESPACE_END
