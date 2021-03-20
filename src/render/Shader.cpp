#include "Shader.h"
#include "../utils/FileUtil.h"
CERAMICS_NAMESPACE_BEGIN
Shader::Shader()
{
}
Shader::~Shader()
{
    clear();
}
void Shader::clear()
{
    if(mShaderId>0)
    {
        glDeleteShader(mShaderId);
        mShaderId = 0;
    }
}
bool Shader::isValid()const
{
    if(mShaderId>0)
    {
        return glIsShader(mShaderId) == GL_TRUE;
    }
    return false;
}

bool Shader::resetByFile(std::string fileName)
{
    clear();
    std::string content;
    if(!FileUtil::getFileContent(fileName,content))
    {
        CERAMICS_LOG_ERROR("Get file content error : %s",fileName.c_str());
        return false;
    }
    return resetByString(content);
}
CERAMICS_NAMESPACE_END
