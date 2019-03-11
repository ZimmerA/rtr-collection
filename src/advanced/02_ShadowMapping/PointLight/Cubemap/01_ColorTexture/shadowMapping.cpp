#include <iostream>
#include <stddef.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "orbitCamera.h"
#include "util.h"
#include "model.h"
#include "textureCubemap.h"
#include "frameBuffer.h"

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 1024;

const unsigned int SMAP_DIM = 512.0f; // Width and height are equal
const float SMAP_NEAR = 1.0f;
const float SMAP_FAR = 100.0f;

const glm::vec3 lightPos(40.f, 50.f, 15.f);

float slopeBias = 1.5;

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

// Controls
OrbitCamera camera;
int lastX = 0;
int lastY = 0;
int mode = 0;
bool altPressed = false;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS)
    {
        altPressed = true;
    } else if (key == GLFW_KEY_LEFT_ALT && action == GLFW_RELEASE)
    {
        altPressed = false;
    }

    if (key == GLFW_KEY_P && action == GLFW_RELEASE)
    {
        slopeBias += 0.1;
        std::cout << slopeBias << std::endl;
    } else if (key == GLFW_KEY_M && action == GLFW_RELEASE)
    {
        slopeBias -= 0.1;
        std::cout << slopeBias << std::endl;
    }

}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        mode = 1;
    } else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {
        mode = 2;
    } else
    {
        mode = 0;
    }
}

static void cursor_position_callback(GLFWwindow *window, double xPos, double yPos)
{
    const int deltaX = xPos - lastX;
    const int deltaY = yPos - lastY;

    lastX = xPos;
    lastY = yPos;
    if (altPressed && mode == 1)
    {
        camera.handleMouseMove(deltaX, deltaY);
    } else if (altPressed && mode == 2)
    {
        camera.movePivotPoint(deltaX, deltaY);
    }

}

void scroll_callback(GLFWwindow *window, double xOffset, double yOffset)
{
    camera.handleMouseWheel(yOffset);
}

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Environment Shadow Mapping: Color Texture", NULL,
                                          NULL);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);

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

    glEnable(GL_DEPTH_TEST);

    // Load cube mesh
    VertexBuffer cubeVbo;
    VertexArray cubeVao;

    cubeVao.bind();
    cubeVbo.buffer(sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    cubeVao.vertexAttribPointer(ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                                (const GLvoid *) 0);
    cubeVao.vertexAttribPointer(ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                                (const GLvoid *) (3 * sizeof(float)));
    cubeVao.vertexAttribPointer(ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                                (const GLvoid *) (6 * sizeof(float)));
    // Load lantern model
    Model lantern;
    lantern.load("models/lantern/Lantern.gltf");

    // Load textures
    Texture whiteTexture;
    int x, y, n;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("res/Textures/Prototype/prototype_512x512_white.png", &x, &y, &n, 0);
    assert(data != NULL);
    whiteTexture.texImage(0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    whiteTexture.texParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    whiteTexture.texParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    whiteTexture.texParameteri(GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    whiteTexture.texParameteri(GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    free(data);

    Texture blueTexture;
    data = stbi_load("res/Textures/Prototype/prototype_512x512_blue2.png", &x, &y, &n, 0);
    assert(data != NULL);
    blueTexture.texImage(0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    blueTexture.texParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    blueTexture.texParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    blueTexture.texParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
    blueTexture.texParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
    free(data);

    // Create shadowmap shaderprogram
    Shader shadowmapVertexShader(GL_VERTEX_SHADER);
    shadowmapVertexShader.attachSourceFromFile("src/advanced/02_ShadowMapping/PointLight/Cubemap/01_ColorTexture/shadowMap.vs");
    Shader shadowmapFragmentShader(GL_FRAGMENT_SHADER);
    shadowmapFragmentShader.attachSourceFromFile("src/advanced/02_ShadowMapping/PointLight/Cubemap/01_ColorTexture/shadowMap.fs");

    ShaderProgram shadowmapProgram;
    shadowmapProgram.attachShader(&shadowmapVertexShader);
    shadowmapProgram.attachShader(&shadowmapFragmentShader);
    shadowmapProgram.linkProgram();
    shadowmapProgram.use();

    GLint mvpUniformLoc = glGetUniformLocation(shadowmapProgram.handle, "mvp");
    GLint modelUniformLoc = glGetUniformLocation(shadowmapProgram.handle, "model");
    GLint lightPosUniformLoc = glGetUniformLocation(shadowmapProgram.handle, "lightPos");

    // Create lighting shaderprogram
    Shader lightingVertexShader(GL_VERTEX_SHADER);
    lightingVertexShader.attachSourceFromFile("src/advanced/02_ShadowMapping/PointLight/Cubemap/01_ColorTexture/light.vs");
    Shader lightingFragmentShader(GL_FRAGMENT_SHADER);
    lightingFragmentShader.attachSourceFromFile("src/advanced/02_ShadowMapping/PointLight/Cubemap/01_ColorTexture/light.fs");

    ShaderProgram lightingProgram;
    lightingProgram.attachShader(&lightingVertexShader);
    lightingProgram.attachShader(&lightingFragmentShader);
    lightingProgram.linkProgram();
    lightingProgram.use();

    GLint lightMvpUniformLoc = glGetUniformLocation(lightingProgram.handle, "mvp");
    GLint lightModelUniformLoc = glGetUniformLocation(lightingProgram.handle, "model");
    GLint lightLightPosUniformLoc = glGetUniformLocation(lightingProgram.handle, "lightPos");
    GLint lightAlbedoUniformLoc = glGetUniformLocation(lightingProgram.handle, "albedo");
    GLint lightslopeBiasUniformLoc = glGetUniformLocation(lightingProgram.handle, "slopeBias");
    glUniform1i(lightAlbedoUniformLoc, 1);

    // Create shaderprogram to visualize light location
    Shader colorVertexShader(GL_VERTEX_SHADER);
    colorVertexShader.attachSourceFromFile("src/advanced/02_ShadowMapping/PointLight/Cubemap/01_ColorTexture/colorShader.vs");
    Shader colorFragmentShader(GL_FRAGMENT_SHADER);
    colorFragmentShader.attachSourceFromFile("src/advanced/02_ShadowMapping/PointLight/Cubemap/01_ColorTexture/colorShader.fs");

    ShaderProgram colorProgram;
    colorProgram.attachShader(&colorVertexShader);
    colorProgram.attachShader(&colorFragmentShader);
    colorProgram.linkProgram();
    colorProgram.use();
    GLint colorMvpUniformLoc = glGetUniformLocation(colorProgram.handle, "mvp");

    // Setup shadowmap Textures and framebuffer for rendering
    TextureCubemap shadowMap;
    shadowMap.texImage(0, GL_R32F, SMAP_DIM, SMAP_DIM, 0, GL_RED, GL_FLOAT,
                       NULL);
    shadowMap.texParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    shadowMap.texParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    shadowMap.texParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    shadowMap.texParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    shadowMap.texParameteri(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    Texture depthBuffer;
    depthBuffer.bind();
    depthBuffer.texImage(0, GL_DEPTH_COMPONENT, SMAP_DIM, SMAP_DIM, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    depthBuffer.texParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    depthBuffer.texParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    depthBuffer.texParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    depthBuffer.texParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    FrameBuffer shadowMapBuffer;
    shadowMapBuffer.bind();
    shadowMapBuffer.attachTexture(GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer.handle, 0);

    // Matrix setup
    glm::mat4 perspective = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / (float) SCR_HEIGHT, 1.f, 1000.0f);
    glm::mat4 lightProj = glm::perspective(glm::radians(90.0f), (float) SMAP_DIM / (float) SMAP_DIM, SMAP_NEAR,
                                           SMAP_FAR);

    glm::mat4 lightViews[6];
    lightViews[0] = lightProj * glm::lookAt(lightPos, lightPos + glm::vec3(1, 0, 0), glm::vec3(0, -1, 0));  // Pos x
    lightViews[1] = lightProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1, 0, 0), glm::vec3(0, -1, 0)); // Neg x
    lightViews[2] = lightProj * glm::lookAt(lightPos, lightPos + glm::vec3(0, 1, 0), glm::vec3(0, 0, 1));   // Pos Y
    lightViews[3] = lightProj * glm::lookAt(lightPos, lightPos + glm::vec3(0, -1, 0), glm::vec3(0, 0, -1)); // Neg y
    lightViews[4] = lightProj * glm::lookAt(lightPos, lightPos + glm::vec3(0, 0, 1), glm::vec3(0, -1, 0));  // Pos z
    lightViews[5] = lightProj * glm::lookAt(lightPos, lightPos + glm::vec3(0, 0, -1), glm::vec3(0, -1, 0)); // Neg z

    glActiveTexture(GL_TEXTURE0);
    shadowMap.bind();
    glActiveTexture(GL_TEXTURE1);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glm::mat4 model(1);
        glm::mat4 mvp(1);

        // Render to shadowmap
        shadowMapBuffer.bind();
        shadowmapProgram.use();
        glUniform3fv(lightPosUniformLoc, 1, glm::value_ptr(lightPos));
        glViewport(0, 0, SMAP_DIM, SMAP_DIM);
        glClearColor(FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX);

        // Iterate over every face of the cubemap
        for (unsigned int i = 0; i < 6; i++)
        {
            shadowMapBuffer.attachTexture(GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, shadowMap.handle,
                                          0);

            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            glm::mat4 vp = lightViews[i];

            // Room
            model = glm::scale(glm::mat4(1), glm::vec3(250.0f));
            model = glm::translate(model, glm::vec3(0, 1, 0));
            mvp = vp * model;
            glUniformMatrix4fv(mvpUniformLoc, 1, GL_FALSE, glm::value_ptr(mvp));
            glUniformMatrix4fv(modelUniformLoc, 1, GL_FALSE, glm::value_ptr(model));
            cubeVao.bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // Draw lantern
            for (auto &mesh : lantern.meshes)
            {
                model = mesh.transform.globalTransform;
                mvp = vp * model;
                glUniformMatrix4fv(mvpUniformLoc, 1, GL_FALSE, glm::value_ptr(mvp));
                glUniformMatrix4fv(modelUniformLoc, 1, GL_FALSE, glm::value_ptr(model));
                mesh.vao.bind();
                glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
            }
        }

        // Lighting pass
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingProgram.use();
        glUniform1f(lightslopeBiasUniformLoc, slopeBias);
        glUniform3fv(lightLightPosUniformLoc, 1, glm::value_ptr(lightPos));

        glm::mat4 vp = perspective * camera.get_view_matrix();

        // Enable front face culling cause were inside the cube
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        whiteTexture.bind();
        model = glm::scale(glm::mat4(1), glm::vec3(250.0f));
        model = glm::translate(model, glm::vec3(0, 1, 0));
        mvp = vp * model;
        glUniformMatrix4fv(lightMvpUniformLoc, 1, GL_FALSE, glm::value_ptr(mvp));
        glUniformMatrix4fv(lightModelUniformLoc, 1, GL_FALSE, glm::value_ptr(model));
        cubeVao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDisable(GL_CULL_FACE);

        // Draw lantern
        blueTexture.bind();
        for (auto &mesh : lantern.meshes)
        {
            mvp = vp * mesh.transform.globalTransform;
            glUniformMatrix4fv(lightMvpUniformLoc, 1, GL_FALSE, glm::value_ptr(mvp));
            glUniformMatrix4fv(lightModelUniformLoc, 1, GL_FALSE, glm::value_ptr(mesh.transform.globalTransform));
            mesh.vao.bind();
            glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
        }

        // Draw cube at light location
        colorProgram.use();
        model = glm::translate(glm::mat4(1), lightPos);
        mvp = vp * model;
        glUniformMatrix4fv(colorMvpUniformLoc, 1, GL_FALSE, glm::value_ptr(mvp));
        cubeVao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
