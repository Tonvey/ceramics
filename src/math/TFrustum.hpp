#pragma once
#include "../CeramicsPrerequisites.h"
CERAMICS_NAMESPACE_BEGIN
template<class T>
struct TFrustum
{
    typedef T value_type;
    typedef TFrustum<T> type;
    typedef TMatrix<T,4,4> matrix_type;
    typedef TPlane<T> plane_type;
    plane_type planes[6];
	TFrustum(plane_type p0,plane_type p1,plane_type p2,plane_type p3,plane_type p4,plane_type p5 ) {
		planes = {p0, p1, p2, p3, p4, p5};
	}

	T &set(plane_type p0,plane_type p1,plane_type p2,plane_type p3,plane_type p4,plane_type p5 ) {

		planes[ 0 ] = p0;
		planes[ 1 ] = p1;
		planes[ 2 ] = p2;
		planes[ 3 ] = p3;
		planes[ 4 ] = p4;
		planes[ 5 ] = p5;

		return *this;

	}

    T &copy(const type &frustum ) {

        for ( size_t i = 0; i < 6; ++i ) {

            planes[ i ] =  frustum.planes[ i ] ;

        }

        return *this;

    }

	void setFromProjectionMatrix(const matrix_type &m ) {

		auto &me = m.elements;
		auto &me0 = &me[ 0 ], me1 = me[ 1 ], &me2 = me[ 2 ], &me3 = me[ 3 ];
		auto &me4 = &me[ 4 ], me5 = me[ 5 ], &me6 = me[ 6 ], &me7 = me[ 7 ];
		auto &me8 = &me[ 8 ], me9 = me[ 9 ], &me10 = me[ 10 ], &me11 = me[ 11 ];
		auto &me12 = &me[ 12 ], me13 = me[ 13 ], &me14 = me[ 14 ], &me15 = me[ 15 ];

		planes[ 0 ].setComponents( me12 - me0, me13 - me1, me14 - me2, me15 - me3 ).normalize();
		planes[ 1 ].setComponents( me12 + me0, me13 + me1, me14 + me2, me15 + me3 ).normalize();
		planes[ 2 ].setComponents( me12 + me4, me13 + me5, me14 + me6, me15 + me7 ).normalize();
		planes[ 3 ].setComponents( me12 - me4, me13 - me5, me14 - me6, me15 - me7 ).normalize();
		planes[ 4 ].setComponents( me12 - me5, me13 - me9, me14 - me10, me15 - me11 ).normalize();
		planes[ 5 ].setComponents( me12 + me5, me13 + me9, me14 + me10, me15 + me11 ).normalize();

		return *this;

	}

	// bool intersectsObject( object ) {

	// 	const geometry = object.geometry;

	// 	if ( geometry.boundingSphere === null ) geometry.computeBoundingSphere();

	// 	_sphere.copy( geometry.boundingSphere ).applyMatrix4( object.matrixWorld );

	// 	return this->intersectsSphere( _sphere );

	// }

	// bool intersectsSprite( sprite ) {

	// 	_sphere.center.set( 0, 0, 0 );
	// 	_sphere.radius = 0.7071067811865476;
	// 	_sphere.applyMatrix4( sprite.matrixWorld );

	// 	return this->intersectsSphere( _sphere );

	// }

	bool intersectsSphere(const TSphere<T> &sphere ) {

		const auto &center = sphere.center;
		const auto negRadius = - sphere.radius;

		for ( size_t i = 0; i < 6; ++i ) {

			auto distance = planes[ i ].distanceToPoint( center );

			if ( distance < negRadius ) {

				return false;

			}

		}

		return true;

	}

	bool intersectsBox(const TBox<T,3> &box )
    {
        TVector<T,3> vector;

		for ( size_t i = 0; i < 6; ++i ) {

			const auto &plane = planes[ i ];
			// corner at max distance

			vector.x = plane.normal.x > 0 ? box.max.x : box.min.x;
			vector.y = plane.normal.y > 0 ? box.max.y : box.min.y;
			vector.z = plane.normal.z > 0 ? box.max.z : box.min.z;

			if ( plane.distanceToPoint( vector ) < 0 ) {

				return false;

			}

		}

		return true;

	}

	bool containsPoint(const TVector<T,3> &point )
    {

		for ( size_t i = 0; i < 6; ++i ) {

			if ( planes[ i ].distanceToPoint( point ) < 0 ) {

				return false;

			}

		}

		return true;

	}

};
CERAMICS_NAMESPACE_END
