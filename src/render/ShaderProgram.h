#pragma once
#include "../CeramicsMacro.h"
#include "../core/Object.h"
#include "Shader.h"
CERAMICS_NAMESPACE_BEGIN
class CERAMICS_EXPORT ShaderProgram : public Object
{
public:
    ShaderProgram();
    ~ShaderProgram();
    ShaderProgram(ShaderProgram &&other);
    ShaderProgram &operator=(ShaderProgram &&other);
    ShaderProgram(const ShaderProgram &other)=delete;
    ShaderProgram &operator=(const ShaderProgram &other)=delete;
    void swap(ShaderProgram &other);
    bool reset(std::string vertFile, std::string fragFile);
    void clear();
    bool isValid()const;
    GLuint getProgramId()const{return mProgramId;}
    GLint getAttr(const std::string &attrName);
    GLint getUniform(const std::string &uniName);
    void use();
    bool linkProgram(Shader *vert,Shader *frag,Shader *tess = nullptr,Shader *Geometry=nullptr);
private:
    GLuint mProgramId = 0;
};
CERAMICS_NAMESPACE_END
