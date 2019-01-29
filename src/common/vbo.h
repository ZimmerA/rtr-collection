#ifndef RTR_COLLECTION_VBO_H
#define RTR_COLLECTION_VBO_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "openGLObjectBase.h"

struct VertexBufferObjectTraits {
    typedef GLuint value_type;

    static value_type create();

    static void destroy(value_type handle);
};

struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
};

class VBO : public OpenGLObjectBase<VertexBufferObjectTraits> {
public:
    void buffer(GLsizeiptr size, const GLvoid *data, GLenum mode);
};

#endif //RTR_COLLECTION_VBO_H
