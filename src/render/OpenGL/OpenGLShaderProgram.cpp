#include "OpenGLShaderProgram.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "OpenGLUtils.h"
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
        OPENGL_UTILS_PRINT_ERROR("glDelteProgram");
        mProgramId = 0;
    }
}
bool OpenGLShaderProgram::isValid()const
{
    if(mProgramId!=0)
    {
        return glIsProgram(mProgramId) == GL_TRUE;
        OPENGL_UTILS_PRINT_ERROR("glIsProgram");
    }
    return false;
}
bool OpenGLShaderProgram::linkProgram(OpenGLShader *vert,OpenGLShader *frag,OpenGLShader *tess,OpenGLShader *geom)
{
    assert(vert&&frag);
    clear();
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vert->getShaderID());
    OPENGL_UTILS_PRINT_ERROR("glAttachShader");
    glAttachShader(programId, frag->getShaderID());
    OPENGL_UTILS_PRINT_ERROR("glAttachShader");
    if(tess!=nullptr)
    {
        glAttachShader(programId, tess->getShaderID());
        OPENGL_UTILS_PRINT_ERROR("glAttachShader");
    }
    if(geom!=nullptr)
    {
        glAttachShader(programId, geom->getShaderID());
        OPENGL_UTILS_PRINT_ERROR("glAttachShader");
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
            CERAMICS_LOG_ERROR("Program info : %s\n",infoLogBuf);
            return false;
        }
    }
    OPENGL_UTILS_PRINT_ERROR("glGetProgramiv");

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
    OPENGL_UTILS_PRINT_ERROR("glDetachShader");
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
        OPENGL_UTILS_PRINT_ERROR("glUseProgram");
    }
}
GLint OpenGLShaderProgram::getAttributeLocation(const std::string &attrName)
{
    auto ret = glGetAttribLocation(mProgramId,attrName.c_str());
    CERAMICS_LOG_DEBUG("getAttributeLocation : %s\n",attrName.c_str());
    OPENGL_UTILS_PRINT_ERROR("glGetAttribLocation");
    return ret;
}

GLint OpenGLShaderProgram::getUniform(const std::string &uniName)
{
    auto ret = glGetUniformLocation(mProgramId,uniName.c_str());
    OPENGL_UTILS_PRINT_ERROR("glGetUniformLocation");
    return ret;
}
void OpenGLShaderProgram::enableVertexAttributeArray(const std::string &attrName)
{
    enableVertexAttributeArray(getAttributeLocation(attrName));
}
void OpenGLShaderProgram::enableVertexAttributeArray(GLint location)
{
    glEnableVertexAttribArray(location);
    OPENGL_UTILS_PRINT_ERROR("glEnableVertexAttribArray");
}
CERAMICS_NAMESPACE_END
