#include "ApplicationBase.h"
#include <iostream>
#include <ctime>
#include <cstring>
#include <memory>
#include <fstream>
#include "FileUtil.h"
using namespace std;

ApplicationBase::~ApplicationBase()
{
    if(mInput!=nullptr)
    {
        mInput->release();
        mInput = nullptr;
    }
    if(mWindow!=nullptr)
    {
        glfwDestroyWindow(mWindow);
        mWindow = nullptr;
    }
}
void ApplicationBase::printOpenGLInfo()
{
    CERAMICS_LOG_DEBUG("OpenGL version: %s\n", glGetString(GL_VERSION));
    CERAMICS_LOG_DEBUG("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    CERAMICS_LOG_DEBUG("Vendor: %s\n", glGetString(GL_VENDOR));
    CERAMICS_LOG_DEBUG("Renderer: %s\n", glGetString(GL_RENDERER));
}

ApplicationBase::ApplicationBase(int argc,char **argv)
    :mWindow(nullptr)
    ,mGLMajorVersion(2)
    ,mGLMinorVersion(1)
{
    for(int i = 0 ; i< argc ; ++i)
    {
        this->mArgvs.push_back(argv[i]);
    }
}

void ApplicationBase::versionSelect()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,this->mGLMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,this->mGLMinorVersion);
}
void ApplicationBase::init()
{
    glfwSetErrorCallback([](int error , const char *description)
    {
        //this->openGLErrorCallBack(error,description);
        cerr<<"Error : "<< error << " " << description << endl;
    });

    //初始化glfw
    if (!glfwInit())
        exit(EXIT_FAILURE);

    //设置OpenGL的版本
    this->versionSelect();

    //创建窗口
    this->mWindow = glfwCreateWindow(
                                     640,
                                     480,
                                     this->mArgvs[0].c_str(),
                                     NULL,
                                     NULL
                                     );
    if(!this->mWindow)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    mInput = new InputGLFW(mWindow);

    //绘制对象
    glfwMakeContextCurrent(this->mWindow);

    //注意glewInit调用的时机，一定是创建完窗口后
    GLenum err = glewInit();
    if(err!= GLEW_OK)
    {
        cerr<<glewGetErrorString(err)<<endl;
        exit(EXIT_FAILURE);
    }

    int width,height;
    glfwGetWindowSize (mWindow, &width, &height);
    glfwSetCursorPos(mWindow, width/2, height/2);

    //垂直同步
    glfwSwapInterval(1);
    glfwSetKeyCallback(this->mWindow,[](GLFWwindow *window,int key,int scancode ,int action ,int mods)
                       {
                           if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                               glfwSetWindowShouldClose(window, GLFW_TRUE);
                       });
}
void ApplicationBase::render(double elapse)
{
    mInput->update();
}

void ApplicationBase::openGLErrorCallBack(int error, const char *description)
{
    cerr<<"Error : "<< error << " " << description << endl;
}

int ApplicationBase::run()
{
    this->init();
    printOpenGLInfo();
    clock_t last_time = clock();
    while (!glfwWindowShouldClose(this->mWindow))
    {
        mInput->update();
        //计算与上一帧时间差（秒）
        clock_t this_time=clock();
        double elapse = (double)(this_time-last_time)/CLOCKS_PER_SEC;
        last_time=this_time;
        //绘制窗口
        this->render(elapse);
    }
    return 0;
}
bool ApplicationBase::createVertexShader(const std::string fileName,GLuint &id)
{
    //创建顶点shader
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    string vertexShaderCode;
    if(!FileUtil::getFileContent(fileName,vertexShaderCode))
    {
        cerr<<"Get file content error : "<<fileName;
        return false;
    }

    //编译vertex shader
    const char *vertexShaderPointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderId, 1, &vertexShaderPointer, NULL);
    glCompileShader(vertexShaderId);

    //检查编译结果
    GLint result = GL_FALSE;
    glGetShaderiv(vertexShaderId,GL_COMPILE_STATUS,&result);
    if(result!=GL_TRUE)//编译出错
    {
        int infoLogLength;
        glGetShaderiv(vertexShaderId,GL_INFO_LOG_LENGTH,&infoLogLength);
        if(infoLogLength>0)
        {
            char *infoLogBuf = new char[infoLogLength+1];
            unique_ptr<char[]> u(infoLogBuf);
            infoLogBuf[infoLogLength] = '\0';
            glGetShaderInfoLog(vertexShaderId,infoLogLength,NULL,infoLogBuf);
            cerr<<"Vertex shader info : "<<infoLogBuf<<endl;
        }
        glDeleteShader(vertexShaderId);
        return false;
    }
    id = vertexShaderId;
    return true;
}
bool ApplicationBase::createFragmentShader(const std::string fileName,GLuint &id)
{
    //创建片段shader
    GLuint fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    string fragShaderCode;
    if(!FileUtil::getFileContent(fileName,fragShaderCode))
    {
        cerr<<"Get file content error : "<<fileName;
        return false;
    }
    //编译frag shader
    const char *fragShaderPointer = fragShaderCode.c_str();
    glShaderSource(fragShaderId, 1, &fragShaderPointer, NULL);
    glCompileShader(fragShaderId);

    //检查编译结果
    GLint result = GL_FALSE;
    glGetShaderiv(fragShaderId,GL_COMPILE_STATUS,&result);
    if(result!=GL_TRUE)//编译出错
    {
        int infoLogLength;
        glGetShaderiv(fragShaderId,GL_INFO_LOG_LENGTH,&infoLogLength);
        if(infoLogLength>0)
        {
            char *infoLogBuf = new char[infoLogLength+1];
            unique_ptr<char[]> u(infoLogBuf);
            infoLogBuf[infoLogLength] = '\0';
            glGetShaderInfoLog(fragShaderId,infoLogLength,NULL,infoLogBuf);
            cerr<<"Frag shader info : "<<infoLogBuf<<endl;
        }
        glDeleteShader(fragShaderId);
        return false;
    }
    id = fragShaderId;
    return true;
}
OpenGLShaderProgram *ApplicationBase::loadShader(string vertShaderFile,string fragShaderFile)
{
    OpenGLShaderProgram *prog = new OpenGLShaderProgram;
    prog->reset(vertShaderFile,fragShaderFile);
    return prog;
}
