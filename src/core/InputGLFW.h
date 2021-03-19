#pragma once
#include "AInput.h"
#include "Ref.h"
#include <map>
#include <vector>
//#include "TEvent.hpp"
CERAMICS_NAMESPACE_BEGIN
class InputGLFW: public AInput , public Ref
{
public:
    struct aaa
    {
        KeyCode code;
    };
    explicit InputGLFW(GLFWwindow *window);
    virtual void update()override;
    virtual bool anyKey()override;
    virtual bool getKey(KeyCode code)override;
    virtual bool getKeyDown(KeyCode code)override;
    virtual bool getKeyUp(KeyCode code)override;

    virtual bool getButton(std::string button)override;
    virtual Real getAxis(std::string axis)override;

    virtual Vector2 mousePosition()override;
    virtual Vector2 mouseScrollDelta()override;
private:
    std::map<int,KeyCode> mGlfwKey2KeyCodeMap;
    std::map<KeyCode,int> mKeyCode2GlfwKeyMap;
    std::vector<int> ala;
    GLFWwindow *mWindow;
    bool mAnyKey=false;
};
CERAMICS_NAMESPACE_END
