#pragma once
#include "../CeramicsMacro.h"
CERAMICS_NAMESPACE_BEGIN
template <class T, size_t dimension>
class TVector;

template<class T>
class TPlane;

template <class T, size_t dimension>
class TBox;

template <class T>
class TTriangle
{
public:
    typedef TTriangle<T> type;
    typedef const type ctype;
    typedef TVector<T, 3> vec_t;
    typedef TPlane<T> plane_t;
    typedef TBox<T, 3> box_t;
    vec_t a, b, c;
    TTriangle(const vec_t& a = vec_t(), const vec_t& b = vec_t(),
              const vec_t& c = vec_t())
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    static vec_t getNormal(const vec_t& a, const vec_t& b, const vec_t& c)
    {
        vec_t target;
        return getNormal(a, b, c, target);
    }
    static vec_t& getNormal(const vec_t& a, const vec_t& b, const vec_t& c,
                            vec_t& target)
    {
        vec_t _v0;
        target.subVectors(c, b);
        _v0.subVectors(a, b);
        target.cross(_v0);
        auto targetLengthSq = target.lengthSq();
        if (targetLengthSq > 0)
        {
            return target.multiplyScalar(1 / std::sqrt(targetLengthSq));
        }
        return target.set(0, 0, 0);
    }

    // static/instance method to calculate barycentric coordinates
    // based on: http://www.blackpawn.com/texts/pointinpoly/default.html
    static vec_t getBarycoord(const vec_t& point, const vec_t& a,
                              const vec_t& b, const vec_t& c)
    {
        vec_t target;
        return getBarycoord(point, a, b, c, target);
    }
    static vec_t& getBarycoord(const vec_t& point, const vec_t& a,
                               const vec_t& b, const vec_t& c, vec_t& target)
    {
        vec_t _v0, _v1, _v2;
        _v0.subVectors(c, a);
        _v1.subVectors(b, a);
        _v2.subVectors(point, a);
        auto dot00 = _v0.dot(_v0);
        auto dot01 = _v0.dot(_v1);
        auto dot02 = _v0.dot(_v2);
        auto dot11 = _v1.dot(_v1);
        auto dot12 = _v1.dot(_v2);
        auto denom = (dot00 * dot11 - dot01 * dot01);
        // collinear or singular triangle
        if (denom == 0)
        {
            // arbitrary location outside of triangle?
            // not sure if this is the best idea, maybe should be returning
            // undefined
            return target.set(-2, -1, -1);
        }
        auto invDenom = 1 / denom;
        auto u = (dot11 * dot02 - dot01 * dot12) * invDenom;
        auto v = (dot00 * dot12 - dot01 * dot02) * invDenom;
        // barycentric coordinates must always sum to 1
        return target.set(1 - u - v, v, u);
    }

    static bool containsPoint(const vec_t& point, const vec_t& a,
                              const vec_t& b, const vec_t& c)
    {
        vec_t _v3;
        getBarycoord(point, a, b, c, _v3);
        return (_v3.x >= 0) && (_v3.y >= 0) && ((_v3.x + _v3.y) <= 1);
    }
    static vec_t getUV(const vec_t& point, const vec_t& p1, const vec_t& p2,
                       const vec_t& p3, const vec_t& uv1, const vec_t& uv2,
                       const vec_t& uv3)
    {
        vec_t target;
        return getUV(point, p1, p2, p3, uv1, uv2, uv3, target);
    }
    static vec_t& getUV(const vec_t& point, const vec_t& p1, const vec_t& p2,
                        const vec_t& p3, const vec_t& uv1, const vec_t& uv2,
                        const vec_t& uv3, vec_t& target)
    {
        vec_t _v3;
        getBarycoord(point, p1, p2, p3, _v3);
        target.set(0, 0);
        target.addScaledVector(uv1, _v3.x);
        target.addScaledVector(uv2, _v3.y);
        target.addScaledVector(uv3, _v3.z);
        return target;
    }
    static bool isFrontFacing(const vec_t& a, const vec_t& b, const vec_t& c,
                              const vec_t& direction)
    {
        vec_t _v0, _v1;
        _v0.subVectors(c, b);
        _v1.subVectors(a, b);
        // strictly front facing
        return (_v0.cross(_v1).dot(direction) < 0) ? true : false;
    }
    type& set(const vec_t& a, const vec_t& b, const vec_t& c)
    {
        this->a.copy(a);
        this->b.copy(b);
        this->c.copy(c);
        return *this;
    }
    type& setFromPointsAndIndices(const vec_t& points, const vec_t& i0,
                                  const vec_t& i1, const vec_t& i2)
    {
        this->a.copy(points[i0]);
        this->b.copy(points[i1]);
        this->c.copy(points[i2]);
        return *this;
    }
    type clone() { return *this; }
    type& operator=(ctype& triangle) { return this->copy(triangle); }
    type& copy(ctype& triangle)
    {
        this->a.copy(triangle.a);
        this->b.copy(triangle.b);
        this->c.copy(triangle.c);
        return *this;
    }
    T getArea()
    {
        vec_t _v0, _v1;
        _v0.subVectors(this->c, this->b);
        _v1.subVectors(this->a, this->b);
        return _v0.cross(_v1).length() * 0.5;
    }
    vec_t getMidpoint()
    {
        vec_t target;
        return this->getMidpoint(target);
    }
    vec_t& getMidpoint(vec_t& target)
    {
        return target.addVectors(this->a, this->b)
            .add(this->c)
            .multiplyScalar(1 / 3);
    }
    vec_t getNormal()
    {
        vec_t taret;
        return getNormal(this->a, this->b, this->c);
    }
    vec_t& getNormal(vec_t& target)
    {
        return getNormal(this->a, this->b, this->c, target);
    }
    plane_t getPlane()
    {
        plane_t target;
        return getPlane(target);
    }
    plane_t& getPlane(plane_t target)
    {
        return target.setFromCoplanarPoints(this->a, this->b, this->c);
    }
    vec_t& getBarycoord(const vec_t& point, vec_t& target)
    {
        return getBarycoord(point, this->a, this->b, this->c, target);
    }
    T getUV(const vec_t& point, const vec_t& uv1, const vec_t& uv2,
            const vec_t& uv3)
    {
        return getUV(point, this->a, this->b, this->c, uv1, uv2, uv3);
    }
    T getUV(const vec_t& point, const vec_t uv1, const vec_t uv2,
            const vec_t uv3, vec_t& target)
    {
        return getUV(point, this->a, this->b, this->c, uv1, uv2, uv3, target);
    }
    bool containsPoint(const vec_t& point)
    {
        return containsPoint(point, this->a, this->b, this->c);
    }
    bool isFrontFacing(const vec_t& direction)
    {
        return isFrontFacing(this->a, this->b, this->c, direction);
    }
    bool intersectsBox(const box_t& box)
    {
        return box.intersectsTriangle(*this);
    }
    vec_t closestPointToPoint(const vec_t& p)
    {
        vec_t target;
        return closestPointToPoint(p, target);
    }
    vec_t& closestPointToPoint(const vec_t& p, vec_t& target)
    {
        auto a = this->a, b = this->b, c = this->c;
        vec_t _vab, _vac, _vap, _vbp, _vcp, _vbc;
        T v, w;

        // algorithm thanks to Real-Time Collision Detection by Christer
        // Ericson, published by Morgan Kaufmann Publishers, (c) 2005 Elsevier
        // Inc., under the accompanying license; see chapter 5.1.5 for detailed
        // explanation. basically, we're distinguishing which of the voronoi
        // regions of the triangle the point lies in with the minimum amount of
        // redundant computation.

        _vab.subVectors(b, a);
        _vac.subVectors(c, a);
        _vap.subVectors(p, a);
        auto d1 = _vab.dot(_vap);
        auto d2 = _vac.dot(_vap);
        if (d1 <= 0 && d2 <= 0)
        {
            // vertex region of A; barycentric coords (1, 0, 0)
            return target.copy(a);
        }

        _vbp.subVectors(p, b);
        auto d3 = _vab.dot(_vbp);
        auto d4 = _vac.dot(_vbp);
        if (d3 >= 0 && d4 <= d3)
        {
            // vertex region of B; barycentric coords (0, 1, 0)
            return target.copy(b);
        }

        auto vc = d1 * d4 - d3 * d2;
        if (vc <= 0 && d1 >= 0 && d3 <= 0)
        {
            v = d1 / (d1 - d3);
            // edge region of AB; barycentric coords (1-v, v, 0)
            return target.copy(a).addScaledVector(_vab, v);
        }

        _vcp.subVectors(p, c);
        auto d5 = _vab.dot(_vcp);
        auto d6 = _vac.dot(_vcp);
        if (d6 >= 0 && d5 <= d6)
        {
            // vertex region of C; barycentric coords (0, 0, 1)
            return target.copy(c);
        }

        auto vb = d5 * d2 - d1 * d6;
        if (vb <= 0 && d2 >= 0 && d6 <= 0)
        {
            w = d2 / (d2 - d6);
            // edge region of AC; barycentric coords (1-w, 0, w)
            return target.copy(a).addScaledVector(_vac, w);
        }

        auto va = d3 * d6 - d5 * d4;
        if (va <= 0 && (d4 - d3) >= 0 && (d5 - d6) >= 0)
        {
            _vbc.subVectors(c, b);
            w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
            // edge region of BC; barycentric coords (0, 1-w, w)
            return target.copy(b).addScaledVector(_vbc,
                                                  w);  // edge region of BC
        }

        // face region
        auto denom = 1 / (va + vb + vc);
        // u = va * denom
        v = vb * denom;
        w = vc * denom;

        return target.copy(a).addScaledVector(_vab, v).addScaledVector(_vac, w);
    }
    bool operator==(ctype& triangle) { return this->equals(triangle); }
    bool equals(ctype& triangle)
    {
        return triangle.a.equals(this->a) && triangle.b.equals(this->b) &&
            triangle.c.equals(this->c);
    }
};
CERAMICS_NAMESPACE_END
