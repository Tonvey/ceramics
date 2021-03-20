#pragma once

#include <string>
#include "../CeramicsMacro.h"
#include "../core/Object.h"
#include "EShaderType.h"
CERAMICS_NAMESPACE_BEGIN
class CERAMICS_EXPORT Shader: public Object{
public:
    Shader();
    virtual ~Shader();
    void clear();
    bool isValid()const;
    virtual EShaderType getShaderType()const = 0;
    bool resetByFile(std::string fileName);
    virtual bool resetByString(const std::string &content) = 0;
    GLuint getShaderID()const{return mShaderId;}
protected:
    GLuint mShaderId = 0;
};
CERAMICS_NAMESPACE_END
