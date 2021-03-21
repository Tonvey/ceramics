#pragma once

#include "../CeramicsType.h"
#include "ApplicationBase.h"
CERAMICS_NAMESPACE_USING

class ApplicationCoreProfile : public ApplicationBase
{
public:
    ApplicationCoreProfile(int argc,char **argv);
    virtual void versionSelect()override;
    void computeMatrixesFromInput(double elapse);
protected:
    Matrix4 mMatView;
    Matrix4 mMatProjection;
    Vector3 mEyePos;
    // float mEyeHorizontalAngle;
    // float mEyeVerticalAngle;
    // float mInitialFoV;
    // float mSpeed;
    // float mMouseSpeed;
};
