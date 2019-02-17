#include <algorithm>

#include "vertexArray.h"

void VertexArray::bind()
{
    glBindVertexArray(handle);
}

void VertexArray::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                                      const GLvoid *pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}
