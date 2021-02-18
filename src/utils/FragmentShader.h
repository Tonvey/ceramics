#pragma once
#include "ShaderBase.h"
class FragmentShader : public ShaderBase
{
public:
    FragmentShader();
    virtual bool resetByContent(const std::string &content)override;
    virtual ShaderType getShaderType()const override
    {
        return Fragment;
    }
};
