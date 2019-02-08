#include <algorithm>
#include <iostream>

#include "vertexBuffer.h"

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

void VertexBuffer::buffer(GLsizeiptr size, const GLvoid *data, GLenum mode)
{
    glBindBuffer(GL_ARRAY_BUFFER, handle);
    glBufferData(GL_ARRAY_BUFFER, size, data, mode);
}