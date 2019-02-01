#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vao.h>
#include <vbo.h>
#include <shader.h>
#include <iostream>
#include <stddef.h>

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
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

    // Create Triangle
    VAO triangleVAO;
    VBO triangleVBO;

    std::vector<Vertex> vertices;
    Vertex vertex;
    vertex.position = glm::vec3(-0.5f, -0.5f, 0.0f);
    vertices.push_back(vertex);
    vertex.position = glm::vec3(0.5f, -0.5f, 0.0f);
    vertices.push_back(vertex);
    vertex.position = glm::vec3(0.0f, 0.5f, 0.0f);
    vertices.push_back(vertex);

    triangleVAO.bind();
    triangleVBO.buffer(sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    triangleVAO.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                    (const GLvoid *) offsetof(Vertex, position));

    Shader vertexShader(GL_VERTEX_SHADER);
    vertexShader.attachSourceFromFile("src/basic/01_HelloTriangle/triangle.vs");
    Shader fragmentShader(GL_FRAGMENT_SHADER);
    fragmentShader.attachSourceFromFile("src/basic/01_HelloTriangle/triangle.fs");

    ShaderProgram shader;
    shader.attachShader(&vertexShader);
    shader.attachShader(&fragmentShader);
    shader.linkProgram();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        triangleVAO.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
