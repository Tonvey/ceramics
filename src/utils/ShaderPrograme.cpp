#include "ShaderPrograme.h"
#include "VertexShader.h"
#include "FragmentShader.h"
using namespace std;


ShaderProgram::ShaderProgram()
{
}
ShaderProgram::~ShaderProgram()
{
    clear();
}
ShaderProgram::ShaderProgram(ShaderProgram &&other)
{
    swap(other);
}
ShaderProgram &ShaderProgram::operator=(ShaderProgram &&other)
{
    clear();
    swap(other);
    return *this;
}
void ShaderProgram::swap(ShaderProgram &other)
{
    GLuint id = mProgramId;
    mProgramId = other.mProgramId;
    other.mProgramId = id;
}
void ShaderProgram::clear()
{
    if(mProgramId!=0)
    {
        glDeleteProgram(mProgramId);
        mProgramId = 0;
    }
}
bool ShaderProgram::isValid()const
{
    if(mProgramId!=0)
    {
        return glIsProgram(mProgramId) == GL_TRUE;
    }
    return false;
}
bool ShaderProgram::reset(std::string vertFile, std::string fragFile)
{
    clear();
    VertexShader vert;
    FragmentShader frag;
    if(!vert.resetByFileName(vertFile))
    {
        exit(-1);
    }
    if(!frag.resetByFileName(fragFile))
    {
        exit(-1);
    }
    //创建程序连接两个shader，得到程序id
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vert.getShaderID());
    glAttachShader(programId, frag.getShaderID());
    glLinkProgram(programId);

    //检查结果
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
    //删除两个shader
    glDetachShader(programId,vert.getShaderID());
    glDetachShader(programId,frag.getShaderID());
    vert.clear();
    frag.clear();
    return true;
}

void ShaderProgram::use()
{
    if(isValid())
    {
        glUseProgram(mProgramId);
    }
}

GLint ShaderProgram::getAttr(const std::string &attrName)
{
    return glGetAttribLocation(mProgramId,attrName.c_str());
}

GLint ShaderProgram::getUniform(const std::string &uniName)
{
    return glGetUniformLocation(mProgramId,uniName.c_str());
}
