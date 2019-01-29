#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define LOADOBJ_IMPLEMENTATION

#include <loadobj.h>

#include <vao.h>
#include <vbo.h>
#include <shader.h>
#include <util.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow(800, 600, "Cube", NULL, NULL);

    glfwMakeContextCurrent(window);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // Load cube mesh
    LoadOBJMesh mesh;
    char *str = loadFile("models/cube.obj");
    loadOBJ(&mesh, str);
    free(str);

    LoadOBJTriangleMesh trimesh;
    loadOBJTriangulate(&trimesh, &mesh);
    loadOBJDestroyMesh(&mesh);
    size_t vertexCount = trimesh.vertexCount;

    VBO cubeVbo;
    VAO cubeVao;
    cubeVao.bind();
    cubeVbo.buffer(trimesh.vertexCount * sizeof(LoadOBJTriangleVertex), trimesh.vertices, GL_STATIC_DRAW);
    cubeVao.vertexAttribPointer(ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(LoadOBJTriangleVertex),
                                (const GLvoid *) offsetof(LoadOBJTriangleVertex, x));
    cubeVao.vertexAttribPointer(ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(LoadOBJTriangleVertex),
                                (const GLvoid *) offsetof(LoadOBJTriangleVertex, nx));
    loadOBJDestroyTriangleMesh(&trimesh);

    // Setup shader
    Shader vs(GL_VERTEX_SHADER);
    vs.attachSourceFromFile("src/basic/02_Cube/cube.vs");
    Shader fs(GL_FRAGMENT_SHADER);
    fs.attachSourceFromFile("src/basic/02_Cube/cube.fs");

    ShaderProgram program;
    program.attachShader(&vs);
    program.attachShader(&fs);
    program.linkProgram();

    GLint mvpUniformLoc = glGetUniformLocation(program.handle, "mvp");
    GLint modelUniformLoc = glGetUniformLocation(program.handle, "model");

    // Setup mvp
    glm::mat4 persp = glm::perspective(70.0f, 800.0f / 600.0f, 0.01f, 100.0f);
    glm::mat4 model = glm::rotate(glm::translate(glm::mat4(1), glm::vec3(-1.0f, 0.0f, -9.0f)), 45.f,
                                  glm::vec3(0, 1, 0));


    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        program.use();
        glm::mat4 mvp = persp * model;
        glUniformMatrix4fv(mvpUniformLoc, 1, GL_FALSE, glm::value_ptr(mvp));
        glUniformMatrix4fv(modelUniformLoc, 1, GL_FALSE, glm::value_ptr(model));
        cubeVao.bind();
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
