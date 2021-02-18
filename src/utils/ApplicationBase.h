#pragma once

#include <vector>
#include <string>
#include "ShaderPrograme.h"

class ApplicationBase
{
public:
    ApplicationBase(int argc,char **argv);
    virtual void init();
    virtual int run();
    virtual void versionSelect();
    virtual void render(double elapse);
    virtual void openGLErrorCallBack(int err,const char *description);
    static ShaderProgram loadShader(std::string vertShaderFile,std::string fragShaderFile);
    static void printOpenGLInfo();
    virtual ~ApplicationBase()=default;
    static bool createVertexShader(const std::string fileName,GLuint &id);
    static bool createFragmentShader(const std::string fileName,GLuint &id);
protected:
    std::vector<std::string> mArgvs;
    GLFWwindow *mWindow;
    int mGLMajorVersion;
    int mGLMinorVersion;
};
