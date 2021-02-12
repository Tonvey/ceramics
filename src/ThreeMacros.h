#pragma once

#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define THREE_NAMESPACE THREE
#define THREE_NAMESPACE_BEGIN namespace THREE_NAMESPACE{
#define THREE_NAMESPACE_END }
#define THREE_NAMESPACE_USING using namespace THREE_NAMESPACE;

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

#define THREE_LOG_DEBUG(...) do{printf(__VA_ARGS__);fflush(stdout);}while(0)
#define THREE_LOG_INFO(...) do{printf(__VA_ARGS__);fflush(stdout);}while(0)
#define THREE_LOG_WARN(...) do{printf(__VA_ARGS__);fflush(stdout);}while(0)
#define THREE_LOG_ERROR(...) do{printf(__VA_ARGS__);fflush(stdout);}while(0)
#define THREE_LOG_FATAL(...) do{printf(__VA_ARGS__);fflush(stdout);}while(0)
#ifdef THREE_TEST 
#define THREE_LOG_TEST(...) do{printf(__VA_ARGS__);fflush(stdout);}while(0)
#else
#define THREE_LOG_TEST(...)
#endif