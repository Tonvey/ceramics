#pragma once
#include "../../core/Object.h"
CERAMICS_NAMESPACE_BEGIN
enum EOpenGLBufferTarget {
    ArrayBuffer             =   GL_ARRAY_BUFFER,
    AtomicCounterBuffer     =   GL_ATOMIC_COUNTER_BUFFER,
    CopyReadBuffer          =   GL_COPY_READ_BUFFER,
    CopyWriteBuffer         =   GL_COPY_WRITE_BUFFER,
    DispatchIndirectBuffer  =   GL_DISPATCH_INDIRECT_BUFFER,
    DrawIndirectBuffer      =   GL_DRAW_INDIRECT_BUFFER,
    ElementArrayBuffer      =   GL_ELEMENT_ARRAY_BUFFER,
    PixelPackBuffer         =   GL_PIXEL_PACK_BUFFER,
    PixelUnpackBuffer       =   GL_PIXEL_UNPACK_BUFFER,
    QueryBuffer             =   GL_QUERY_BUFFER,
    ShaderStorageBuffer     =   GL_SHADER_STORAGE_BUFFER,
    TextureBuffer           =   GL_TEXTURE_BUFFER,
    TransformFeedbackBuffer =   GL_TRANSFORM_FEEDBACK_BUFFER,
    UniformBuffer           =   GL_UNIFORM_BUFFER,
};
enum EOpenGLBufferUsagePattern {
    StreamDraw      =   GL_STREAM_DRAW,
    StreamRead      =   GL_STREAM_READ,
    StreamCopy      =   GL_STREAM_COPY,
    StaticDraw      =   GL_STATIC_DRAW,
    StaticRead      =   GL_STATIC_READ,
    StaticCopy      =   GL_STATIC_COPY,
    DynamicDraw     =   GL_DYNAMIC_DRAW,
    DynamicRead     =   GL_DYNAMIC_READ,
    DynamicCopy     =   GL_DYNAMIC_COPY,
};
class OpenGLBuffer : public Object
{
public:
    OpenGLBuffer();
    virtual ~OpenGLBuffer();
    void bind();
    void setTarget(EOpenGLBufferTarget target){ mTarget=static_cast<EOpenGLBufferTarget>(target);}
    EOpenGLBufferTarget getTarget()const {return mTarget;}
    void setUsagePattern(EOpenGLBufferUsagePattern pattern){mUsage = static_cast<EOpenGLBufferUsagePattern>(pattern);}
    EOpenGLBufferUsagePattern getUsagePattern()const {return mUsage;}
    GLuint getBufferName()const{return mBufferName;}
    void write(const void *data, size_t byteCount,size_t offset = 0);
    bool read(void *data, size_t byteCount ,size_t offset = 0);
private:
    EOpenGLBufferTarget mTarget = ArrayBuffer;
    EOpenGLBufferUsagePattern mUsage = StaticDraw;
    GLuint mBufferName = GL_INVALID_VALUE;
};
CERAMICS_NAMESPACE_END
