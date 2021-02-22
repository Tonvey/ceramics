#include "Camera.h"
CERAMICS_NAMESPACE_BEGIN

Vector3 Camera::getWorldDirection( ) {

    Vector3 ret;
        
    // this->updateWorldMatrix( true, false );
    this->updateMatrixWorld();

    const auto e = this->mMatrixWorld.elements;

    return ret.set( - e[ 8 ], - e[ 9 ], - e[ 10 ] ).normalize();

}

void Camera::updateMatrixWorld() {

    Node3D::updateMatrixWorld();
    this->mMatrixWorldInverse =  this->mMatrixWorld.getInverse();

}

Matrix4 Camera::getMatrixWorldInverse()
{
    updateMatrixWorld();
    return mMatrixWorldInverse;
}

// void Camera::updateWorldMatrix(bool updateParents,bool updateChildren ) {

//     Node3D::updateWorldMatrix( updateParents, updateChildren );

//     this->mMatrixWorldInverse = this->mMatrixWorld.getInverse();

// }
CERAMICS_NAMESPACE_END
