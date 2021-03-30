#include "VertexShader.h"
#include <memory>
#include "OpenGLUtils.h"
using namespace std;
CERAMICS_NAMESPACE_BEGIN
VertexShader::VertexShader()
{
}
bool VertexShader::resetByString(const std::string &content)
{
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    CERAMICS_OPENGL_CHECK_ERROR("glCreateShader");
    //编译vertex shader
    const char *vertexShaderPointer = content.c_str();
    glShaderSource(vertexShaderId, 1, &vertexShaderPointer, NULL);
    CERAMICS_OPENGL_CHECK_ERROR("glShaderSource");
    glCompileShader(vertexShaderId);
    CERAMICS_OPENGL_CHECK_ERROR("glCompileShader");

    //检查编译结果
    GLint result = GL_FALSE;
    glGetShaderiv(vertexShaderId,GL_COMPILE_STATUS,&result);
    if(result!=GL_TRUE)//编译出错
    {
        int infoLogLength;
        glGetShaderiv(vertexShaderId,GL_INFO_LOG_LENGTH,&infoLogLength);
        CERAMICS_OPENGL_CHECK_ERROR("glGetShaderiv");
        if(infoLogLength>0)
        {
            char *infoLogBuf = new char[infoLogLength+1];
            unique_ptr<char[]> u(infoLogBuf);
            infoLogBuf[infoLogLength] = '\0';
            glGetShaderInfoLog(vertexShaderId,infoLogLength,NULL,infoLogBuf);
            CERAMICS_OPENGL_CHECK_ERROR("glGetShaderInfoLog");
            CERAMICS_LOG_ERROR("Vertex shader info : %s",infoLogBuf);
        }
        glDeleteShader(vertexShaderId);
        CERAMICS_OPENGL_CHECK_ERROR("glDeleteShader");
        return false;
    }
    mShaderId = vertexShaderId;
    return true;
}
CERAMICS_NAMESPACE_END
