#include <iostream>
#include <assert.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "shader.h"
#include "util.h"
#include "model.h"
#include "texture.h"
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Normal Mapping", NULL, NULL);
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

    // Load 3D model
    Model m;
    m.load("models/lantern/Lantern.gltf");

    // Load textures
    Texture albedo;
    albedo.texParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    albedo.texParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Texture normal;
    normal.texParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    normal.texParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int x, y, n;

    unsigned char *data = stbi_load("models/lantern/Lantern_baseColor.png", &x, &y, &n, 0);
    assert(data != NULL);
    albedo.texImage(0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    free(data);

    data = stbi_load("models/lantern/Lantern_normal.png", &x, &y, &n, 0);
    assert(data != NULL);
    normal.texImage(0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    free(data);

    glActiveTexture(GL_TEXTURE0);
    albedo.bind();
    glActiveTexture(GL_TEXTURE1);
    normal.bind();

    // Setup shader
    Shader vs(GL_VERTEX_SHADER);
    vs.attachSourceFromFile("src/basic/04_NormalMapping/nm.vs");
    Shader fs(GL_FRAGMENT_SHADER);
    fs.attachSourceFromFile("src/basic/04_NormalMapping/nm.fs");

    ShaderProgram program;
    program.attachShader(&vs);
    program.attachShader(&fs);
    program.linkProgram();
    program.use();

    GLint mvpUniformLoc = glGetUniformLocation(program.handle, "mvp");
    GLint modelUniformLoc = glGetUniformLocation(program.handle, "model");
    GLint albedoUniformLoc = glGetUniformLocation(program.handle, "albedoMap");
    GLint normalUniformLoc = glGetUniformLocation(program.handle, "normalMap");

    glUniform1i(albedoUniformLoc, 0);
    glUniform1i(normalUniformLoc, 1);

    // Setup mvp matrices
    glm::mat4 perspective = glm::perspective(70.0f, 800.0f / 600.0f, 0.01f, 1000.0f);
    glm::mat4 model = glm::rotate(glm::translate(glm::mat4(1), glm::vec3(-1.0f, 0.0f, -80.0f)), 45.f,
                                  glm::vec3(0, 1, 0));

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        program.use();

        for (auto &mesh : m.meshes)
        {
            model = glm::rotate(glm::translate(glm::mat4(1), glm::vec3(0.0f, -13.0f, -30.0f)),
                                float(1.0 * glfwGetTime()),
                                glm::vec3(0, 1, 0));

            model *= mesh.transform.globalTransform;
            glm::mat4 mvp = perspective * model;

            glUniformMatrix4fv(mvpUniformLoc, 1, GL_FALSE, glm::value_ptr(mvp));
            glUniformMatrix4fv(modelUniformLoc, 1, GL_FALSE, glm::value_ptr(model));
            mesh.vao.bind();
            glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
        }

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
