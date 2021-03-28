#pragma once
#include "../../core/Object.h"
CERAMICS_NAMESPACE_BEGIN
enum EOpenGLAttributeType{
};
class OpenGLVertexAttributeArray : public Object
{
public:
    OpenGLVertexAttributeArray();
    virtual ~OpenGLVertexAttributeArray();
private:
    GLuint mPositionName = GL_INVALID_VALUE;
};
CERAMICS_NAMESPACE_END
