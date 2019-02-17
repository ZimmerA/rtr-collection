#ifndef RTR_COLLECTION_VAO_H
#define RTR_COLLECTION_VAO_H

#include "glad/glad.h"
#include "glTraits.h"
#include "openGLObjectBase.h"

class VertexArray : public OpenGLObjectBase<VertexArrayObjectTraits> {
public:
    void bind();

    void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                             const GLvoid *pointer);
};

#endif //RTR_COLLECTION_VAO_H
