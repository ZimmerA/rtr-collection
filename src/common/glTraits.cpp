#include "glTraits.h"

ShaderProgramTraits::value_type ShaderProgramTraits::create()
{
    return glCreateProgram();
}

void ShaderProgramTraits::destroy(ShaderProgramTraits::value_type handle)
{
    glDeleteProgram(handle);
}

TextureTraits::value_type TextureTraits::create()
{
    value_type handle;
    glGenTextures(1, &handle);
    return handle;
}

void TextureTraits::destroy(TextureTraits::value_type handle)
{
    glDeleteTextures(1, &handle);
}

VertexArrayObjectTraits::value_type VertexArrayObjectTraits::create()
{
    value_type handle;
    glGenVertexArrays(1, &handle);
    return handle;
}

void VertexArrayObjectTraits::destroy(VertexArrayObjectTraits::value_type handle)
{
    glDeleteVertexArrays(1, &handle);
}

VertexBufferObjectTraits::value_type VertexBufferObjectTraits::create()
{
    value_type handle;
    glGenBuffers(1, &handle);
    return handle;
}

void VertexBufferObjectTraits::destroy(VertexBufferObjectTraits::value_type handle)
{
    glDeleteBuffers(1, &handle);
}

FrameBufferTraits::value_type FrameBufferTraits::create()
{
    value_type handle;
    glGenFramebuffers(1, &handle);
    return handle;
}

void FrameBufferTraits::destroy(FrameBufferTraits::value_type handle)
{
    glDeleteFramebuffers(1, &handle);
}