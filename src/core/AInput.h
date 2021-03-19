#pragma once
#include "../CeramicsType.h"
#include "EKeyCode.h"
CERAMICS_NAMESPACE_BEGIN
class AInput
{
public:
    virtual void update()=0;

    virtual bool anyKey()=0;
    virtual bool getKey(KeyCode code)=0;
    virtual bool getKeyDown(KeyCode code)=0;
    virtual bool getKeyUp(KeyCode code)=0;

    virtual bool getButton(std::string button)=0;
    virtual Real getAxis(std::string axis)=0;

    virtual Vector2 mousePosition()=0;
    virtual Vector2 mouseScrollDelta()=0;

};
CERAMICS_NAMESPACE_END
