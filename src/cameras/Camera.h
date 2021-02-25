#pragma once
#include "../core/Node3D.h"
CERAMICS_NAMESPACE_BEGIN
class Camera : public Node3D {
public:
    typedef Camera type;
    virtual ~Camera(){};
    virtual Vector3 getWorldDirection();
    // virtual void updateMatrixWorld(bool force) override;
    virtual void updateMatrixWorld() override;
    // virtual void updateWorldMatrix(bool updateParents,bool updateChildren) override;
    Matrix4 getProjectionMatrix(){return mProjectionMatrix;};
    Matrix4 getProjectionMatrixInverse(){return mProjectionMatrixInverse;};
    Matrix4 getMatrixWorldInverse();
    virtual void updateProjectionMatrix() = 0;

protected:
    Camera(){}
    Matrix4 mProjectionMatrix;
    Matrix4 mProjectionMatrixInverse;
    Matrix4 mMatrixWorldInverse;

};
CERAMICS_NAMESPACE_END
