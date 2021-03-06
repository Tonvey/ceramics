#pragma once
#include "../core/Node3D.h"
CERAMICS_NAMESPACE_BEGIN
class Camera : public Node3D {
public:
    typedef Camera type;
    virtual ~Camera(){};
    // virtual void updateMatrixWorld(bool force) override;
    virtual void updateMatrixWorld() override;
    // virtual void updateWorldMatrix(bool updateParents,bool updateChildren) override;
    Matrix4 getProjectionMatrix();
    Matrix4 getProjectionMatrixInverse();
    Matrix4 getMatrixWorldInverse();
    virtual void updateProjectionMatrix() = 0;
    // virtual void lookAt(const Vector3 &target)override;

protected:
    Camera(){}
    Matrix4 mProjectionMatrix;
    Matrix4 mProjectionMatrixInverse;
    Matrix4 mMatrixWorldInverse;

};
CERAMICS_NAMESPACE_END
