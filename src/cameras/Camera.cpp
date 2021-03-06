#include "Camera.h"
CERAMICS_NAMESPACE_BEGIN

void Camera::updateMatrixWorld()
{

    Node3D::updateMatrixWorld();
    this->mMatrixWorldInverse =  this->mMatrixWorld.getInverse();

}
Matrix4 Camera::getProjectionMatrix()
{
    updateProjectionMatrix();
    return mProjectionMatrix;
}
Matrix4 Camera::getProjectionMatrixInverse()
{
    updateProjectionMatrix();
    return mProjectionMatrixInverse;
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

// void Camera::lookAt(const Vector3 &target)
// {
//     Vector3 position = this->mPosition;
//     Matrix4 m;
//     Quaternion q;

//     // this->updateWorldMatrix(true, false);
//     // TODO rewrite in subclass
//     // position.setFromMatrixPosition(this->mMatrixWorld);

//     m.lookAt(position, target, this->mUp);

//     this->mQuaternion.setFromRotationMatrix(m);

//     auto originParent = mParent.lock();
//     if (originParent != nullptr)
//     {
//         m.extractRotation(originParent->getMatrixWorld());
//         q.setFromRotationMatrix(m);
//         this->mQuaternion.premultiply(q.inverse());
//     }
//     this->mEuler.setFromQuaternion(mQuaternion);
//     mMatrixLocalNeedUpdate = true;
// }
CERAMICS_NAMESPACE_END
