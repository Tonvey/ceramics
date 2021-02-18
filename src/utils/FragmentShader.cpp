#include "FragmentShader.h"
#include <memory>
using namespace std;
FragmentShader::FragmentShader()
{
}
bool FragmentShader::resetByContent(const std::string &content)
{
    GLuint fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    //编译frag shader
    const char *fragShaderPointer = content.c_str();
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
            CERAMICS_LOG_ERROR("Frag shader info : %s",infoLogBuf);
        }
        glDeleteShader(fragShaderId);
        return false;
    }
    mShaderId = fragShaderId;
    return true;
}
