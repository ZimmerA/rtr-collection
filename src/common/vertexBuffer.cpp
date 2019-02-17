#include <algorithm>
#include <iostream>

#include "vertexBuffer.h"

void VertexBuffer::buffer(GLsizeiptr size, const GLvoid *data, GLenum mode)
{
    glBindBuffer(GL_ARRAY_BUFFER, handle);
    glBufferData(GL_ARRAY_BUFFER, size, data, mode);
}
