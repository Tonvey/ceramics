#include "OpenGLUtils.h"
CERAMICS_NAMESPACE_BEGIN
void OpenGLUtils::printWhenError(std::string tag , bool needExit /*= true*/)
{
    auto err = glGetError();
    if(err!=GL_NO_ERROR)
    {
        CERAMICS_LOG_ERROR("OpenGL Error %s %d:%s\n",tag.c_str(),err,OpenGLUtils::getErrorString(err).c_str());
        if(needExit)
            exit(-1);
    }
}
std::string OpenGLUtils::getErrorString(GLenum err)
{
    std::string ret;
    switch(err)
    {
    case GL_NO_ERROR:
        //No error has been recorded. The value of this symbolic constant is guaranteed to be 0.
        ret = "No Error";
        break;
    case GL_INVALID_ENUM:
        //An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.
        ret = "Invalid Enum";
        break;
    case GL_INVALID_VALUE:
        //A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.
        ret = "Invalid Value";
        break;
    case GL_INVALID_OPERATION:
        //The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.
        ret = "Invalid Operation";
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        //The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.
        ret = "Invalid Framebuffer Operation";
        break;
    case GL_OUT_OF_MEMORY:
        //There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.
        ret = "Out Of Memory";
        break;
    case GL_STACK_UNDERFLOW:
        //An attempt has been made to perform an operation that would cause an internal stack to underflow.
        ret = "Stack Underflow";
        break;
    case GL_STACK_OVERFLOW:
        //An attempt has been made to perform an operation that would cause an internal stack to overflow. 
        ret = "Stack Overflow";
        break;
    default:
        ret = "Unknown Error";
        break;
    }
    return ret;
}
CERAMICS_NAMESPACE_END
