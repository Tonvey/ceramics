#pragma once
#include "OpenGLShader.h"
CERAMICS_NAMESPACE_BEGIN
class CERAMICS_EXPORT VertexShader : public OpenGLShader
{
public:
    VertexShader();
    virtual bool resetByString(const std::string &content)override;
    virtual EShaderType getShaderType()const override
    {
        return EShaderType::Vertex;
    }
};
CERAMICS_NAMESPACE_END
