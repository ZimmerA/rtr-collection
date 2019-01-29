#ifndef RTR_COLLECTION_VAO_H
#define RTR_COLLECTION_VAO_H

#include <glad/glad.h>
#include "openGLObjectBase.h"

struct VertexArrayObjectTraits {
    typedef GLuint value_type;

    static value_type create();

    static void destroy(value_type handle);
};

class VAO : public OpenGLObjectBase<VertexArrayObjectTraits> {
public:
    void bind();

    void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                             const GLvoid *pointer);
};


#endif //RTR_COLLECTION_VAO_H
