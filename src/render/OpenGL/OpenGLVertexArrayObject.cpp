#include "OpenGLVertexArrayObject.h"
CERAMICS_NAMESPACE_BEGIN
OpenGLVertexArrayObject::OpenGLVertexArrayObject()
{
    glGenVertexArrays(1,&mVAOName);
    if(mVAOName==GL_INVALID_VALUE)
    {
        CERAMICS_LOG_ERROR("glGenVertexArrays error");
    }
}
OpenGLVertexArrayObject::~OpenGLVertexArrayObject()
{
    if(mVAOName!=GL_INVALID_VALUE&&
       glIsVertexArray(mVAOName)==GL_TRUE)
    {
        glDeleteVertexArrays(1,&mVAOName);
    }
}
void OpenGLVertexArrayObject::bind()
{
    glBindVertexArray(mVAOName);
}
CERAMICS_NAMESPACE_END
