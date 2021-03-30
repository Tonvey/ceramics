#pragma once
#include <string>
#include "../../CeramicsMacro.h"
#define CERAMICS_RENDER_API_DEBUG
CERAMICS_NAMESPACE_BEGIN
#ifdef CERAMICS_RENDER_API_DEBUG
#define CERAMICS_OPENGL_CHECK_ERROR(tag)                                \
    do{OpenGLUtils::checkError(std::string(tag)+":"+__FILE__+":"+std::to_string(__LINE__));}while(0)
#else
#define OPENGL_UTILS_PRINT_ERROR(tag)
#endif
class OpenGLUtils
{
public:
    static void checkError(std::string tag);
    static std::string getErrorString(GLenum err);
};
CERAMICS_NAMESPACE_END
