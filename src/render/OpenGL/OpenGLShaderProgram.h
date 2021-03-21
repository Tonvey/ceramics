#pragma once
#include "../../CeramicsMacro.h"
#include "../../core/Object.h"
#include "OpenGLShader.h"
CERAMICS_NAMESPACE_BEGIN
class CERAMICS_EXPORT OpenGLShaderProgram : public Object
{
public:
    OpenGLShaderProgram();
    ~OpenGLShaderProgram();
    OpenGLShaderProgram(OpenGLShaderProgram &&other);
    OpenGLShaderProgram &operator=(OpenGLShaderProgram &&other);
    OpenGLShaderProgram(const OpenGLShaderProgram &other)=delete;
    OpenGLShaderProgram &operator=(const OpenGLShaderProgram &other)=delete;
    void swap(OpenGLShaderProgram &other);
    bool reset(std::string vertFile, std::string fragFile);
    void clear();
    bool isValid()const;
    GLuint getProgramId()const{return mProgramId;}
    GLint getAttr(const std::string &attrName);
    GLint getUniform(const std::string &uniName);
    void use();
    bool linkProgram(OpenGLShader *vert,OpenGLShader *frag,OpenGLShader *tess = nullptr,OpenGLShader *Geometry=nullptr);
private:
    GLuint mProgramId = 0;
};
CERAMICS_NAMESPACE_END
