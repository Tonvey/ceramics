#include "ShaderBase.h"
#include "FileUtil.h"
ShaderBase::ShaderBase()
{
}
ShaderBase::~ShaderBase()
{
    clear();
}
void ShaderBase::clear()
{
    if(mShaderId>0)
    {
        glDeleteShader(mShaderId);
        mShaderId = 0;
    }
}
bool ShaderBase::isValid()const
{
    if(mShaderId>0)
    {
        return glIsShader(mShaderId) == GL_TRUE;
    }
    return false;
}

bool ShaderBase::resetByFileName(std::string fileName)
{
    clear();
    std::string content;
    if(!FileUtil::getFileContent(fileName,content))
    {
        CERAMICS_LOG_ERROR("Get file content error : %s",fileName.c_str());
        return false;
    }
    return resetByContent(content);
}
