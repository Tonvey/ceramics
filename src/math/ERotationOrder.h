#pragma once
#include "../CeramicsMacro.h"
CERAMICS_NAMESPACE_BEGIN
typedef enum
{
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
}RotationOrder;
CERAMICS_NAMESPACE_END
