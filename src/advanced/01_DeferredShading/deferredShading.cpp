#include <iostream>
#include <stddef.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "shader.h"
#include "util.h"
#include "frameBuffer.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

float cubeVertices[] = {
        // back face
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
        1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
        -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, // top-left
        // front face
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
        1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // bottom-right
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
        -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // top-left
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
        // left face
        -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
        -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
        -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
        -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
        -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-right
        -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
        // right face
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
        1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
        1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left
        // bottom face
        -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
        1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-left
        1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
        1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
        -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
        -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
        // top face
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
        1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
        -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f  // bottom-left
};

// Press E to toggle gBuffer preview on/off
bool previewGBuffer = true;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        previewGBuffer = !previewGBuffer;
}

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Deferred Shading", NULL, NULL);

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

    glfwSetKeyCallback(window, key_callback);

    glViewport(0, 0, 800, 600);
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // Setup g buffer
    FrameBuffer gBuffer;

    Texture gPosition(GL_TEXTURE_2D);
    gPosition.texImage2D(0, GL_RGB16F, 800, 600, 0, GL_RGB, GL_FLOAT, NULL);
    gPosition.texParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gPosition.texParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gBuffer.attachTexture2D(GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

    Texture gNormal(GL_TEXTURE_2D);
    gNormal.texImage2D(0, GL_RGB16F, 800, 600, 0, GL_RGB, GL_FLOAT, NULL);
    gNormal.texParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gNormal.texParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gBuffer.attachTexture2D(GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

    Texture gColorSpec(GL_TEXTURE_2D);
    gColorSpec.texImage2D(0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    gColorSpec.texParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gColorSpec.texParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gBuffer.attachTexture2D(GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gColorSpec, 0);

    unsigned int attachments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    glDrawBuffers(3, attachments);

    // Load cube model

    VertexBuffer cubeVbo;
    VertexArray cubeVao;

    cubeVao.bind();
    cubeVbo.buffer(sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    cubeVao.vertexAttribPointer(ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
                                (const GLvoid *) 0);
    cubeVao.vertexAttribPointer(ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
                                (const GLvoid *) (sizeof(float) * 3));

    // Create screen quad
    VertexArray quadVAO;
    VertexBuffer quadVBO;
    ShaderProgram shader;

    std::vector<Vertex> vertices;
    Vertex vertex;
    vertex.position = glm::vec3(-1.0f, 1.0f, 0.0f); // Top left
    vertex.uv = glm::vec2(0.0f, 1.0f);
    vertices.push_back(vertex);
    vertex.position = glm::vec3(-1.0f, -1.0f, 0.0f); // Bottom left
    vertex.uv = glm::vec2(0.0f, 0.0f);
    vertices.push_back(vertex);
    vertex.position = glm::vec3(1.0f, -1.0f, 0.0f); // Bottom right
    vertex.uv = glm::vec2(1.0f, 0.0f);
    vertices.push_back(vertex);
    vertex.position = glm::vec3(1.0f, 1.0f, 0.0f); // Top right
    vertex.uv = glm::vec2(1.0f, 1.0f);
    vertices.push_back(vertex);

    quadVAO.bind();
    quadVBO.buffer(sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    quadVAO.vertexAttribPointer(ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                (const GLvoid *) offsetof(Vertex, position));
    quadVAO.vertexAttribPointer(ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                (const GLvoid *) offsetof(Vertex, uv));

    // Create gBuffer shader
    Shader gVS(GL_VERTEX_SHADER);
    gVS.attachSourceFromFile("src/advanced/01_DeferredShading/gShader.vs");
    Shader gFS(GL_FRAGMENT_SHADER);
    gFS.attachSourceFromFile("src/advanced/01_DeferredShading/gShader.fs");

    ShaderProgram gProgram;
    gProgram.attachShader(&gVS);
    gProgram.attachShader(&gFS);
    gProgram.linkProgram();

    gProgram.use();
    GLint gMvpUniformLocation = glGetUniformLocation(gProgram.handle, "mvp");
    GLint gModelUniformLoc = glGetUniformLocation(gProgram.handle, "model");

    // Create gBuffer preview shader
    Shader previewVS(GL_VERTEX_SHADER);
    previewVS.attachSourceFromFile("src/advanced/01_DeferredShading/previewShader.vs");
    Shader previewFS(GL_FRAGMENT_SHADER);
    previewFS.attachSourceFromFile("src/advanced/01_DeferredShading/previewShader.fs");

    ShaderProgram previewProgram;
    previewProgram.attachShader(&previewVS);
    previewProgram.attachShader(&previewFS);
    previewProgram.linkProgram();

    previewProgram.use();
    GLint previewTexUniformLocation = glGetUniformLocation(previewProgram.handle, "screenTexture");
    GLint previewModeUniformLocation = glGetUniformLocation(previewProgram.handle, "defaultMode");
    glUniform1i(previewTexUniformLocation, 0);

    // Create lighting Shader
    Shader lightingVS(GL_VERTEX_SHADER);
    lightingVS.attachSourceFromFile("src/advanced/01_DeferredShading/lightingShader.vs");
    Shader lightingFS(GL_FRAGMENT_SHADER);
    lightingFS.attachSourceFromFile("src/advanced/01_DeferredShading/lightingShader.fs");

    ShaderProgram lightingProgram;
    lightingProgram.attachShader(&lightingVS);
    lightingProgram.attachShader(&lightingFS);
    lightingProgram.linkProgram();

    lightingProgram.use();
    GLint lightingPosUniformLocation = glGetUniformLocation(lightingProgram.handle, "gPosition");
    glUniform1i(lightingPosUniformLocation, 0);
    GLint lightingNormalUniformLocation = glGetUniformLocation(lightingProgram.handle, "gNormal");
    glUniform1i(lightingNormalUniformLocation, 1);
    GLint lightingColorSpecUniformLocation = glGetUniformLocation(lightingProgram.handle, "gAlbedoSpec");
    glUniform1i(lightingColorSpecUniformLocation, 2);
    GLint lightingViewPosUniformLocation = glGetUniformLocation(lightingProgram.handle, "viewPos");
    glUniform3fv(lightingViewPosUniformLocation, 1, glm::value_ptr(glm::vec3(0.0f)));

    // Setup mvp
    glm::mat4 perspective = glm::perspective(70.0f, 800.0f / 600.0f, 0.01f, 600.0f);
    glm::mat4 model = glm::rotate(glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, -5.0f)), 45.f,
                                  glm::vec3(0, 1, 0));

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glEnable(GL_SCISSOR_TEST);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        // G pass
        gBuffer.bind();
        glViewport(0, 0, 800, 600);
        glScissor(0, 0, 800, 600);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gProgram.use();
        cubeVao.bind();
        model = glm::rotate(glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, -5.0f)), float(1.0 * glfwGetTime()),
                            glm::vec3(0, 1, 0));
        glm::mat4 mvp = perspective * model;
        glUniformMatrix4fv(gMvpUniformLocation, 1, GL_FALSE, glm::value_ptr(mvp));
        glUniformMatrix4fv(gModelUniformLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (previewGBuffer) // Preview passes
        {
            glActiveTexture(GL_TEXTURE0);
            previewProgram.use();
            quadVAO.bind();

            // Draw Position
            glViewport(0, 300, 400, 300);
            glScissor(0, 300, 400, 300);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            gPosition.bind();
            glUniform1i(previewModeUniformLocation, 1);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

            // Draw Normal
            glViewport(400, 300, 400, 300);
            glScissor(400, 300, 400, 300);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            gNormal.bind();
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

            // Draw Albedo
            glViewport(0, 0, 400, 300);
            glScissor(0, 0, 400, 300);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            gColorSpec.bind();
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

            // Draw Spec
            glViewport(400, 0, 400, 300);
            glScissor(400, 0, 400, 300);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUniform1i(previewModeUniformLocation, 0);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        } else // Lighting pass
        {
            glActiveTexture(GL_TEXTURE0);
            gPosition.bind();
            glActiveTexture(GL_TEXTURE1);
            gNormal.bind();
            glActiveTexture(GL_TEXTURE2);
            gColorSpec.bind();
            lightingProgram.use();
            quadVAO.bind();
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        }

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
