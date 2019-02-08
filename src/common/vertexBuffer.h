#ifndef RTR_COLLECTION_VBO_H
#define RTR_COLLECTION_VBO_H

#include <vector>

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "openGLObjectBase.h"

struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

struct VertexBufferObjectTraits {
    typedef GLuint value_type;

    static value_type create();

    static void destroy(value_type handle);
};

class VertexBuffer : public OpenGLObjectBase<VertexBufferObjectTraits> {
public:
    void buffer(GLsizeiptr size, const GLvoid *data, GLenum mode);
};

#endif //RTR_COLLECTION_VBO_H
