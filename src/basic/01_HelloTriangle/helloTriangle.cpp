#include <iostream>
#include <stddef.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vao.h>
#include <vbo.h>
#include <shader.h>
#include <util.h>

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Triangle!", NULL, NULL);

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

    // Define the viewport dimensions
    glViewport(0, 0, 800, 600);

    VAO triangleVAO;
    VBO triangleVBO;
    ShaderProgram shader;

    std::vector<Vertex> vertices;
    Vertex vertex;
    vertex.position = glm::vec3(-0.5f, -0.5f, 0.0f);
    vertices.push_back(vertex);
    vertex.position = glm::vec3(0.5f, -0.5f, 0.0f);
    vertices.push_back(vertex);
    vertex.position = glm::vec3(0.0f, 0.5f, 0.0f);
    vertices.push_back(vertex);

    const char *vs = loadFile("src/basic/01_HelloTriangle/triangle.vs");
    const char *fs = loadFile("src/basic/01_HelloTriangle/triangle.fs");
    Shader vertexShader(GL_VERTEX_SHADER);
    vertexShader.attachSource(&vs);
    Shader fragmentShader(GL_FRAGMENT_SHADER);
    fragmentShader.attachSource(&fs);
    shader.attachShader(&vertexShader);
    shader.attachShader(&fragmentShader);
    shader.linkProgram();

    triangleVAO.bind();
    triangleVBO.buffer(sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    triangleVAO.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                    (const GLvoid *) offsetof(Vertex, position));

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        triangleVAO.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
