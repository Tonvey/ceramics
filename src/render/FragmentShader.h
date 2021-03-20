#pragma once
#include "Shader.h"
CERAMICS_NAMESPACE_BEGIN
class CERAMICS_EXPORT FragmentShader : public Shader
{
public:
    FragmentShader();
    virtual bool resetByString(const std::string &content)override;
    virtual EShaderType getShaderType()const override
    {
        return EShaderType::Fragment;
    }
};
CERAMICS_NAMESPACE_END
