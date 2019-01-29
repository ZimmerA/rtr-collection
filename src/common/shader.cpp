#include <algorithm>
#include "shader.h"
#include<iostream>
#include<util.h>
#include<stdlib.h>

/*
 * Shader
 */
Shader::Shader(GLenum shaderType)
{
    handle = glCreateShader(shaderType);
    type = shaderType;
}

Shader::~Shader()
{
    glDeleteShader(handle);
}

void Shader::attachSource(const GLchar **source)
{
    glShaderSource(handle, 1, source, NULL);
    glCompileShader(handle);

    int success;
    char infoLog[512];
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(handle, 512, NULL, infoLog);
        std::string shader;
        switch (type)
        {
            case GL_VERTEX_SHADER:
                shader = "VERTEX";
                break;
            case GL_FRAGMENT_SHADER:
                shader = "FRAGMENT";
                break;
            case GL_GEOMETRY_SHADER:
                shader = "GEOMETRY";
                break;
            case GL_TESS_CONTROL_SHADER:
                shader = "TESS_CONTROL";
                break;
            case GL_TESS_EVALUATION_SHADER:
                shader = "TESS_EVALUATION";
                break;
            case GL_COMPUTE_SHADER:
                shader = "COMPUTE";
                break;
        }
        std::cout << "ERROR::SHADER::" << shader << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::attachSourceFromFile(const char *path)
{
    const char *data = loadFile(path);
    attachSource(&data);
    free((void*)data);
}

/*
 * ShaderProgram
 */
ShaderProgramTraits::value_type ShaderProgramTraits::create()
{
    return glCreateProgram();
}

void ShaderProgramTraits::destroy(ShaderProgramTraits::value_type handle)
{
    glDeleteProgram(handle);
}

void ShaderProgram::attachShader(Shader *shader)
{
    glAttachShader(handle, shader->handle);
}

void ShaderProgram::linkProgram()
{
    glLinkProgram(handle);

    int success;
    char infoLog[512];

    glGetProgramiv(handle, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(handle, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

void ShaderProgram::use()
{
    glUseProgram(handle);
}
