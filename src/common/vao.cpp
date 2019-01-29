#include "vao.h"
#include <glad/glad.h>
#include <algorithm>

void VAO::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                              const GLvoid *pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}

VertexArrayObjectTraits::value_type VertexArrayObjectTraits::create()
{
    value_type handle;
    glGenVertexArrays(1, &handle);
    return handle;
}

void VAO::bind()
{
    glBindVertexArray(handle);
}

void VertexArrayObjectTraits::destroy(VertexArrayObjectTraits::value_type handle)
{
    glDeleteVertexArrays(1, &handle);
}
