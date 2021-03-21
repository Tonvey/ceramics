#pragma once
#include "OpenGLShader.h"
CERAMICS_NAMESPACE_BEGIN
class CERAMICS_EXPORT FragmentShader : public OpenGLShader
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
