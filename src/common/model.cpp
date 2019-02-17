#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>

#include "model.h"
#include "shader.h"
#include "glm/gtc/type_ptr.hpp"

Transform::Transform(glm::mat4 localTransform, glm::mat4 globalTransform) : localTransform(localTransform),
                                                                            globalTransform(globalTransform)
{

}

Mesh::Mesh(std::vector<Vertex> vertices, GLsizei vertexCount, Transform transform) : vertexCount(vertexCount),
                                                                                     transform(transform)
{
    vao.bind();
    vbo.buffer(vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    vao.vertexAttribPointer(ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                            (const GLvoid *) offsetof(Vertex, position));
    vao.vertexAttribPointer(ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                            (const GLvoid *) offsetof(Vertex, uv));
    vao.vertexAttribPointer(ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                            (const GLvoid *) offsetof(Vertex, normal));
    vao.vertexAttribPointer(ATTRIBUTE_TANGENT, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                            (const GLvoid *) offsetof(Vertex, tangent));
    vao.vertexAttribPointer(ATTRIBUTE_BITANGENT, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                            (const GLvoid *) offsetof(Vertex, bitangent));
}

Model::Model() : parentTransform(glm::mat4(1), glm::mat4(1))
{

}

Model::~Model()
{

}

int Model::load(const char *path)
{
    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;
    bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, path);

    if (!warn.empty())
    {
        printf("Warn: %s\n", warn.c_str());
    }

    if (!err.empty())
    {
        printf("Err: %s\n", err.c_str());
    }

    if (!ret)
    {
        printf("Failed to parse glTF\n");
        return -1;
    }

    tinygltf::Scene *defaultScene = &model.scenes[model.defaultScene];

    for (int n : defaultScene->nodes)
    {
        iterateNodeHierarchyRecursive(model, n, parentTransform);
    }
    return 1;
}

void Model::iterateNodeHierarchyRecursive(tinygltf::Model &model, int nodeIndex, Transform &parentTransform)
{
    tinygltf::Node *currentNode = &model.nodes[nodeIndex];

    // Get the translation of the Node
    glm::vec3 translation(0, 0, 0);

    if (currentNode->translation.size() == 3)
    {
        translation = glm::make_vec3(currentNode->translation.data());
    }

    // Build the local transform matrix
    glm::mat4 localTransform = glm::translate(glm::mat4(1), translation);
    glm::mat4 globalTransform = localTransform * parentTransform.globalTransform;
    Transform transform(localTransform, globalTransform);
    int meshIndex = currentNode->mesh;

    // Process Mesh if there
    if (meshIndex != -1)
    {
        tinygltf::Mesh *mesh = &model.meshes[meshIndex];
        std::vector<Vertex> vertices;
        GLsizei vertexCount = 0;

        for (auto p : mesh->primitives)
        {
            // Get attributes
            const float *positions = nullptr;
            const float *normals = nullptr;
            const float *texcoords = nullptr;
            const float *tangents = nullptr;

            for (const std::pair<const std::string, int> &attribute : p.attributes)
            {
                const tinygltf::Accessor &accessor = model.accessors[attribute.second];
                const tinygltf::BufferView &bufferView = model.bufferViews[accessor.bufferView];
                const tinygltf::Buffer &buffer = model.buffers[bufferView.buffer];

                if (attribute.first.compare("POSITION") == 0)
                {
                    positions = reinterpret_cast<const float *>(&buffer.data[bufferView.byteOffset +
                                                                             accessor.byteOffset]);
                } else if (attribute.first.compare("TEXCOORD_0") == 0)
                {
                    texcoords = reinterpret_cast<const float *>(&buffer.data[bufferView.byteOffset +
                                                                             accessor.byteOffset]);
                } else if (attribute.first.compare("NORMAL") == 0)
                {
                    normals = reinterpret_cast<const float *>(&buffer.data[bufferView.byteOffset +
                                                                           accessor.byteOffset]);
                } else if (attribute.first.compare("TANGENT") == 0)
                {
                    tangents = reinterpret_cast<const float *>(&buffer.data[bufferView.byteOffset +
                                                                            accessor.byteOffset]);
                }
            }

            const tinygltf::Accessor &accessorIndex = model.accessors[p.indices];
            const tinygltf::BufferView &bufferViewIndex = model.bufferViews[accessorIndex.bufferView];
            const tinygltf::Buffer &bufferIndex = model.buffers[bufferViewIndex.buffer];

            const unsigned short *indices = reinterpret_cast<const unsigned short *>(&bufferIndex.data[
                    bufferViewIndex.byteOffset + accessorIndex.byteOffset]);

            Vertex v;
            for (size_t i = 0; i < accessorIndex.count; ++i)
            {
                unsigned short index = indices[i];

                if (positions)
                {
                    v.position = glm::vec3(positions[index * 3 + 0], positions[index * 3 + 1],
                                           positions[index * 3 + 2]);
                }

                if (texcoords)
                {
                    v.uv = glm::vec2(texcoords[index * 2 + 0], texcoords[index * 2 + 1]);
                }

                if (normals)
                {
                    v.normal = glm::vec3(normals[index * 3 + 0], normals[index * 3 + 1], normals[index * 3 + 2]);
                    if (tangents)
                    {
                        v.tangent = glm::vec3(tangents[index * 4 + 0], tangents[index * 4 + 1],
                                              tangents[index * 4 + 2]);
                        v.bitangent = glm::cross(v.normal, v.tangent) * tangents[index * 4 + 3];
                    }
                }
                vertices.push_back(v);
                vertexCount++;
            }
            meshes.push_back(std::move(Mesh(vertices, vertexCount, transform)));
        }
    }

    for (int childIndex : currentNode->children)
    {
        iterateNodeHierarchyRecursive(model, childIndex, parentTransform);
    }
}
