#pragma once
#include "../ThreeMacros.h"
THREE_NAMESPACE_BEGIN
typedef enum {
    XYZ,
    XZY,
    YXZ,
    YZX,
    ZXY,
    ZYX,

    XYX,
    YZY,
    ZXZ,
    XZX,
    YXY,
    ZYZ,
} RotationOrder;
THREE_NAMESPACE_END