#ifndef RTR_COLLECTION_MODEL_H
#define RTR_COLLECTION_MODEL_H

#include <vector>

#include "vertexBuffer.h"
#include "vertexArray.h"
#include "tiny_gltf.h"


class Transform {
public:
    glm::mat4 localTransform;
    glm::mat4 globalTransform;

    Transform() = default;

    Transform(glm::mat4 localTransform, glm::mat4 globalTransform);
};

class Mesh {
public:
    Transform transform;
    VertexArray vao;
    VertexBuffer vbo;
    GLsizei vertexCount;

    Mesh(std::vector<Vertex>, GLsizei vertexCount, Transform transform);
};

class Model {
public:
    Transform parentTransform;
    std::vector<Mesh> meshes;

    Model();

    ~Model();

    int load(const char *path);

    void iterateNodeHierarchyRecursive(tinygltf::Model &model, int nodeIndex, Transform &parentTransform);
};

#endif //RTR_COLLECTION_MODEL_H
