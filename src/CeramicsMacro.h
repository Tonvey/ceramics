#pragma once

#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define CERAMICS_NAMESPACE CERAMICS
#define CERAMICS_NAMESPACE_BEGIN namespace CERAMICS_NAMESPACE{
#define CERAMICS_NAMESPACE_END }
#define CERAMICS_NAMESPACE_USING using namespace CERAMICS_NAMESPACE;

#ifdef __APPLE__
#   include <GLUT/glut.h>
#else
#define GL_GLEXT_PROTOTYPES
#   include <GL/glut.h>
#endif

#include <cmath>
const double PI = std::atan(1.0)*4;

#ifndef EM_PORT_API
#	if defined(__EMSCRIPTEN__)
#       define CERAMICS_EMSCRIPTEN
#		include <emscripten.h>
#		if defined(__cplusplus)
#			define EM_PORT_API(rettype) extern "C" rettype EMSCRIPTEN_KEEPALIVE
#		else
#			define EM_PORT_API(rettype) rettype EMSCRIPTEN_KEEPALIVE
#		endif
#	else
#		if defined(__cplusplus)
#			define EM_PORT_API(rettype) extern "C" rettype
#		else
#			define EM_PORT_API(rettype) rettype
#		endif
#	endif
#endif

#define CERAMICS_LOG_DEBUG(...) do{printf(__VA_ARGS__);fflush(stdout);}while(0)
#define CERAMICS_LOG_INFO(...) do{printf(__VA_ARGS__);fflush(stdout);}while(0)
#define CERAMICS_LOG_WARN(...) do{printf(__VA_ARGS__);fflush(stdout);}while(0)
#define CERAMICS_LOG_ERROR(...) do{printf(__VA_ARGS__);fflush(stdout);}while(0)
#define CERAMICS_LOG_FATAL(...) do{printf(__VA_ARGS__);fflush(stdout);}while(0)
#ifdef CERAMICS_TEST 
#define CERAMICS_LOG_TEST(...) do{printf(__VA_ARGS__);fflush(stdout);}while(0)
#else
#define CERAMICS_LOG_TEST(...)
#endif
