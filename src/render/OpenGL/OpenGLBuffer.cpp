#include "OpenGLBuffer.h"
CERAMICS_NAMESPACE_BEGIN
OpenGLBuffer::OpenGLBuffer()
{
    glGenBuffers(1, &mBufferName);
    if(mBufferName==GL_INVALID_VALUE)
    {
        CERAMICS_LOG_ERROR("glGenBuffers error");
    }
}
OpenGLBuffer::~OpenGLBuffer()
{
    if(
       mBufferName!=GL_INVALID_VALUE&&
       glIsBuffer(mBufferName)==GL_TRUE)
    {
        glDeleteBuffers(1,&mBufferName);
    }
}
void OpenGLBuffer::bind()
{
    glBindBuffer(mTarget,mBufferName);
}
void OpenGLBuffer::write(const void *data, size_t byteCount, size_t offset /*= 0*/)
{
    bind();
    glBufferData(
                 mTarget,
                 byteCount,
                 static_cast<const uint8_t*>(data) + offset,
                 mUsage);
}
CERAMICS_NAMESPACE_END
