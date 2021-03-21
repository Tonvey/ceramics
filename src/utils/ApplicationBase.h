#pragma once

#include <vector>
#include <string>
#include "../render/OpenGL/OpenGLShaderProgram.h"
#include "../core/InputGLFW.h"
CERAMICS_NAMESPACE_USING

class ApplicationBase
{
public:
    ApplicationBase(int argc,char **argv);
    virtual ~ApplicationBase();
    virtual void init();
    virtual int run();
    virtual void versionSelect();
    virtual void render(double elapse);
    virtual void openGLErrorCallBack(int err,const char *description);
    static OpenGLShaderProgram *loadShader(std::string vertShaderFile,std::string fragShaderFile);
    static void printOpenGLInfo();
    static bool createVertexShader(const std::string fileName,GLuint &id);
    static bool createFragmentShader(const std::string fileName,GLuint &id);
protected:
    std::vector<std::string> mArgvs;
    GLFWwindow *mWindow;
    InputGLFW *mInput;
    int mGLMajorVersion;
    int mGLMinorVersion;
};
