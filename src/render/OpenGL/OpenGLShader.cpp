#include "OpenGLShader.h"
#include "../../utils/FileUtil.h"
CERAMICS_NAMESPACE_BEGIN
OpenGLShader::OpenGLShader()
{
}
OpenGLShader::~OpenGLShader()
{
    clear();
}
void OpenGLShader::clear()
{
    if(mShaderId>0)
    {
        glDeleteShader(mShaderId);
        mShaderId = 0;
    }
}
bool OpenGLShader::isValid()const
{
    if(mShaderId>0)
    {
        return glIsShader(mShaderId) == GL_TRUE;
    }
    return false;
}

bool OpenGLShader::resetByFile(std::string fileName)
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
