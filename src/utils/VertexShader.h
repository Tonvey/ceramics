#pragma once
#include "ShaderBase.h"
class VertexShader : public ShaderBase
{
public:
    VertexShader();
    virtual bool resetByContent(const std::string &content)override;
    virtual ShaderType getShaderType()const override
    {
        return Vertex;
    }
};
