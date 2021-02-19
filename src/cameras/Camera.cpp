#include "Camera.h"
CERAMICS_NAMESPACE_BEGIN

Vector3 Camera::getWorldDirection( ) {

    Vector3 ret;
        
    this->updateWorldMatrix( true, false );

    const auto e = this->matrixWorld.elements;

    return ret.set( - e[ 8 ], - e[ 9 ], - e[ 10 ] ).normalize();

}

void Camera::updateMatrixWorld(bool force ) {

    Object3D::updateMatrixWorld( force );

    this->matrixWorldInverse =  this->matrixWorld.getInverse();

}

void Camera::updateWorldMatrix(bool updateParents,bool updateChildren ) {

    Object3D::updateWorldMatrix( updateParents, updateChildren );

    this->matrixWorldInverse = this->matrixWorld.getInverse();

}
CERAMICS_NAMESPACE_END
