#pragma once

#include <memory>
#include "../CeramicsType.h"

class ShaderProgram
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
private:
    GLuint mProgramId = 0;
};
