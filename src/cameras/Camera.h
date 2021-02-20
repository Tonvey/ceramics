#pragma once
#include "../core/Object3D.h"
CERAMICS_NAMESPACE_BEGIN
class Camera : public Object3D {
public:
    typedef Camera type;
    Matrix4 matrixWorldInverse;
    Matrix4 projectionMatrix;
    Matrix4 projectionMatrixInverse;
    virtual ~Camera(){};
    virtual Vector3 getWorldDirection();
    virtual void updateMatrixWorld(bool force) override;
    virtual void updateWorldMatrix(bool updateParents,bool updateChildren) override;
    virtual void updateProjectionMatrix() = 0;
protected:
    Camera(){}

};
CERAMICS_NAMESPACE_END
