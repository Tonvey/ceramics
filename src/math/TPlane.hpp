#pragma once
#include <stdexcept>
#include "../CeramicsPrerequisites.h"
CERAMICS_NAMESPACE_BEGIN
template<class T>
struct TPlane
{
    typedef T value_type;
    typedef TPlane<T> type;
    typedef TVector<T, 3> vec3_t;
    typedef TSphere<T> sphere_t;
    typedef TBox<T,3> box3_t;
    typedef TMatrix<T,4,4> matrix4_t;
    typedef TLine<T,3> line3_t;
    vec3_t normal;
    T constant;
    TPlane( vec3_t normal = vec3_t(T(1),T(0),T(0)), T constant = T(0))
        : normal(normal),constant(constant){ }

    type &set(const vec3_t &normal,T constant )
    {

        this->normal.copy( normal );
        this->constant = constant;

        return *this;

    }

    type &setComponents(T x,T y,T z,T w )
    {

        this->normal.set( x, y, z );
        this->constant = w;

        return *this;

    }

    type &setFromNormalAndCoplanarPoint(const vec3_t &normal, const vec3_t &point )
    {

        this->normal.copy( normal );
        this->constant = - point.dot( this->normal );

        return *this;

    }

    type &setFromCoplanarPoints(const vec3_t& a,const vec3_t& b,const vec3_t& c )
    {

        vec3_t _vector1,_vector2;
        auto normal = _vector1.subVectors( c, b ).cross( _vector2.subVectors( a, b ) ).normalize();

        this->setFromNormalAndCoplanarPoint( normal, a );

        return *this;

    }

    type clone()
    {

        return *this;

    }

    type &operator=(const type &plane )
    {
        return this->copy(plane);
    }
    type &copy(const type &plane )
    {

        this->normal.copy( plane.normal );
        this->constant = plane.constant;

        return *this;

    }

    type &normalize()
    {

        // Note: will lead to a divide by zero if the plane is invalid.

        auto inverseNormalLength = T(1.0) / this->normal.length();
        this->normal.multiplyScalar( inverseNormalLength );
        this->constant *= inverseNormalLength;

        return *this;

    }

    type &negate()
    {

        this->constant *= T(- 1);
        this->normal.negate();

        return *this;

    }

    T distanceToPoint(const vec3_t & point )
    {

        return this->normal.dot( point ) + this->constant;

    }

    T distanceToSphere(const sphere_t &sphere )
    {

        return this->distanceToPoint( sphere.center ) - sphere.radius;

    }

    vec3_t &projectPoint(const vec3_t &point)
    {
        vec3_t target;
        return this->projectPoint(point,target);
    }
    vec3_t &projectPoint(const vec3_t &point,vec3_t &target )
    {

        return target.copy( this->normal ).multiplyScalar( - this->distanceToPoint( point ) ).add( point );

    }

    vec3_t &intersectLine(const line3_t line)
    {
        vec3_t target; 
        return intersectLine(line,target);
    }
    vec3_t &intersectLine(const line3_t line,vec3_t &target )
    {
        vec3_t _vector1;
        auto direction = line.delta( _vector1 );

        auto denominator = this->normal.dot( direction );

        if ( denominator == T(0) )
        {

            // line is coplanar, return origin
            if ( this->distanceToPoint( line.start ) == T(0) )
            {

                return target.copy( line.start );

            }

            // Unsure if this is the correct method to handle this case.
            // return undefined;
            throw std::runtime_error("Unsure if this is the correct method to handle this case");

        }

        auto t = - ( line.start.dot( this->normal ) + this->constant ) / denominator;

        if ( t < 0 || t > 1 )
        {

            // return undefined;
            throw std::runtime_error("Undefined");

        }

        return target.copy( direction ).multiplyScalar( t ).add( line.start );

    }

    bool intersectsLine(const line3_t line )
    {

        // Note: this tests if a line intersects the plane, not whether it (or its end-points) are coplanar with it.

        auto startSign = this->distanceToPoint( line.start );
        auto endSign = this->distanceToPoint( line.end );

        return ( startSign < 0 && endSign > 0 ) || ( endSign < 0 && startSign > 0 );

    }

    bool intersectsBox(const box3_t &box )
    {

        return box.intersectsPlane( *this );

    }

    bool intersectsSphere( const sphere_t &sphere )
    {

        return sphere.intersectsPlane(*this );

    }

    vec3_t coplanarPoint() const
    {

        vec3_t target;

        return this->coplanarPoint(target);

    }

    vec3_t &coplanarPoint(vec3_t &target ) const
    {

        return target.copy( this->normal ).multiplyScalar( - this->constant );

    }

    type &applyMatrix4(const matrix4_t &matrix)
    {
        matrix4_t optionalNormalMatrix ;
        return this->applyMatrix4(matrix,optionalNormalMatrix);
    }
    type &applyMatrix4(const matrix4_t &matrix,const matrix4_t &optionalNormalMatrix )
    {

        vec3_t _vector1;
        matrix4_t _normalMatrix;

        auto normalMatrix = optionalNormalMatrix || _normalMatrix.getNormalMatrix( matrix );

        auto referencePoint = this->coplanarPoint( _vector1 ).applyMatrix4( matrix );

        auto normal = this->normal.applyMatrix3( normalMatrix ).normalize();

        this->constant = - referencePoint.dot( normal );

        return *this;

    }

    type &translate(const vec3_t &offset )
    {

        this->constant -= offset.dot( this->normal );

        return *this;

    }

    bool operator==(const type &plane )
    {
        return this->equals(plane);
    }
    bool equals(const type &plane )
    {

        return plane.normal.equals( this->normal ) && ( plane.constant == this->constant );

    }

};
CERAMICS_NAMESPACE_END
