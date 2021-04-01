#pragma once
#include "IInput.h"
#include <map>
#include <vector>
//#include "TEvent.hpp"
CERAMICS_NAMESPACE_BEGIN
class CERAMICS_EXPORT InputGLFW: public IInput
{
public:
    struct aaa
    {
        EKeyCode code;
    };
    explicit InputGLFW(GLFWwindow *window);
    virtual void update()override;
    virtual bool anyKey()override;
    virtual bool getKey(EKeyCode code)override;
    virtual bool getKeyDown(EKeyCode code)override;
    virtual bool getKeyUp(EKeyCode code)override;

    virtual bool getButton(std::string button)override;
    virtual Real getAxis(std::string axis)override;

    virtual Vector2 mousePosition()override;
    virtual Vector2 mouseScrollDelta()override;
private:
    std::map<int,EKeyCode> mGlfwKey2EKeyCodeMap;
    std::map<EKeyCode,int> mEKeyCode2GlfwKeyMap;
    std::vector<int> ala;
    GLFWwindow *mWindow;
    bool mAnyKey=false;
};
CERAMICS_NAMESPACE_END
