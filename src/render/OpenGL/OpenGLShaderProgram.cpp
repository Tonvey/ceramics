#include "OpenGLShaderProgram.h"
#include "VertexShader.h"
#include "FragmentShader.h"
using namespace std;
CERAMICS_NAMESPACE_BEGIN
OpenGLShaderProgram::OpenGLShaderProgram()
{
}
OpenGLShaderProgram::~OpenGLShaderProgram()
{
    clear();
}
OpenGLShaderProgram::OpenGLShaderProgram(OpenGLShaderProgram &&other)
{
    swap(other);
}
OpenGLShaderProgram &OpenGLShaderProgram::operator=(OpenGLShaderProgram &&other)
{
    clear();
    swap(other);
    return *this;
}
void OpenGLShaderProgram::swap(OpenGLShaderProgram &other)
{
    GLuint id = mProgramId;
    mProgramId = other.mProgramId;
    other.mProgramId = id;
}
void OpenGLShaderProgram::clear()
{
    if(mProgramId!=0)
    {
        glDeleteProgram(mProgramId);
        mProgramId = 0;
    }
}
bool OpenGLShaderProgram::isValid()const
{
    if(mProgramId!=0)
    {
        return glIsProgram(mProgramId) == GL_TRUE;
    }
    return false;
}
bool OpenGLShaderProgram::linkProgram(OpenGLShader *vert,OpenGLShader *frag,OpenGLShader *tess,OpenGLShader *geom)
{
    assert(vert&&frag);
    clear();
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vert->getShaderID());
    glAttachShader(programId, frag->getShaderID());
    if(tess!=nullptr)
    {
        glAttachShader(programId, tess->getShaderID());
    }
    if(geom!=nullptr)
    {
        glAttachShader(programId, geom->getShaderID());
    }
    glLinkProgram(programId);

    GLint result = GL_FALSE;
    glGetProgramiv(programId,GL_LINK_STATUS,&result);
    if(result!=GL_TRUE)//编译出错
    {
        int infoLogLength;
        glGetProgramiv(programId,GL_INFO_LOG_LENGTH,&infoLogLength);
        if(infoLogLength>0)
        {
            char *infoLogBuf = new char[infoLogLength+1];
            unique_ptr<char[]> u(infoLogBuf);
            infoLogBuf[infoLogLength] = '\0';
            glGetProgramInfoLog(programId,infoLogLength,NULL,infoLogBuf);
            CERAMICS_LOG_ERROR("Program info : %s",infoLogBuf);
            return false;
        }
    }

    mProgramId = programId;
    //取消shader附属
    glDetachShader(programId,vert->getShaderID());
    glDetachShader(programId,frag->getShaderID());
    if(tess!=nullptr)
    {
        glDetachShader(programId,tess->getShaderID());
    }
    if(geom!=nullptr)
    {
        glDetachShader(programId,geom->getShaderID());
    }
    return true;
}
bool OpenGLShaderProgram::reset(std::string vertFile, std::string fragFile)
{
    RefUniquePtr<VertexShader> vert(new VertexShader);
    RefUniquePtr<FragmentShader> frag(new FragmentShader);
    if(!vert->resetByFile(vertFile))
    {
        exit(-1);
    }
    if(!frag->resetByFile(fragFile))
    {
        exit(-1);
    }
    
    return linkProgram(vert.get(),frag.get());
}

void OpenGLShaderProgram::use()
{
    if(isValid())
    {
        glUseProgram(mProgramId);
    }
}
GLint OpenGLShaderProgram::getAttr(const std::string &attrName)
{
    return glGetAttribLocation(mProgramId,attrName.c_str());
}

GLint OpenGLShaderProgram::getUniform(const std::string &uniName)
{
    return glGetUniformLocation(mProgramId,uniName.c_str());
}
CERAMICS_NAMESPACE_END
