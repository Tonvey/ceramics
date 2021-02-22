#pragma once
#include "../core/Node3D.h"
CERAMICS_NAMESPACE_BEGIN
class Camera : public Node3D {
public:
    typedef Camera type;
    Matrix4 projectionMatrix;
    Matrix4 projectionMatrixInverse;
    virtual ~Camera(){};
    virtual Vector3 getWorldDirection();
    // virtual void updateMatrixWorld(bool force) override;
    virtual void updateMatrixWorld() override;
    // virtual void updateWorldMatrix(bool updateParents,bool updateChildren) override;
    virtual void updateProjectionMatrix() = 0;
    Matrix4 getMatrixWorldInverse();

protected:
    Camera(){}
    Matrix4 mMatrixWorldInverse;

};
CERAMICS_NAMESPACE_END
