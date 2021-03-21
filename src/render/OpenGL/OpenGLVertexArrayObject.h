#pragma once
#include "../../core/Object.h"
CERAMICS_NAMESPACE_BEGIN
class OpenGLVertexArrayObject : public Object
{
public:
    OpenGLVertexArrayObject();
    virtual ~OpenGLVertexArrayObject();
    void bind();
private:
    GLuint mVAOName = GL_INVALID_VALUE;
};
CERAMICS_NAMESPACE_END
