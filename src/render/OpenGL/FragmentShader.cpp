#include "FragmentShader.h"
#include <memory>
#include "OpenGLUtils.h"
using namespace std;
CERAMICS_NAMESPACE_BEGIN
FragmentShader::FragmentShader()
{
}
bool FragmentShader::resetByString(const std::string &content)
{
    GLuint fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    CERAMICS_OPENGL_CHECK_ERROR("glCreateShader");
    //编译frag shader
    const char *fragShaderPointer = content.c_str();
    glShaderSource(fragShaderId, 1, &fragShaderPointer, NULL);
    CERAMICS_OPENGL_CHECK_ERROR("glShaderSource");
    glCompileShader(fragShaderId);
    CERAMICS_OPENGL_CHECK_ERROR("glCompileShader");

    //检查编译结果
    GLint result = GL_FALSE;
    glGetShaderiv(fragShaderId,GL_COMPILE_STATUS,&result);
    CERAMICS_OPENGL_CHECK_ERROR("glGetShaderiv");
    if(result!=GL_TRUE)//编译出错
    {
        int infoLogLength;
        glGetShaderiv(fragShaderId,GL_INFO_LOG_LENGTH,&infoLogLength);
        CERAMICS_OPENGL_CHECK_ERROR("glGetShaderiv");
        if(infoLogLength>0)
        {
            char *infoLogBuf = new char[infoLogLength+1];
            unique_ptr<char[]> u(infoLogBuf);
            infoLogBuf[infoLogLength] = '\0';
            glGetShaderInfoLog(fragShaderId,infoLogLength,NULL,infoLogBuf);
            CERAMICS_OPENGL_CHECK_ERROR("glGetShaderInfoLog");
            CERAMICS_LOG_ERROR("Frag shader info : %s",infoLogBuf);
        }
        glDeleteShader(fragShaderId);
        CERAMICS_OPENGL_CHECK_ERROR("glDeleteShader");
        return false;
    }
    mShaderId = fragShaderId;
    return true;
}
CERAMICS_NAMESPACE_END
