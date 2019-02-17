#ifndef RTR_COLLECTION_SHADER_H
#define RTR_COLLECTION_SHADER_H

#define ATTRIBUTE_POSITION 0
#define ATTRIBUTE_TEXCOORD 1
#define ATTRIBUTE_NORMAL 2
#define ATTRIBUTE_TANGENT 3
#define ATTRIBUTE_BITANGENT 4

#include "glad/glad.h"
#include "glTraits.h"
#include "openGLObjectBase.h"

class Shader {
public:
    GLuint handle;

    Shader(GLenum shaderType);

    ~Shader();

    void attachSource(const GLchar **source);

    void attachSourceFromFile(const char *path);

private:
    GLenum type;
};


class ShaderProgram : public OpenGLObjectBase<ShaderProgramTraits> {
public:
    void attachShader(Shader *shader);

    void linkProgram();

    void use();
};

#endif //RTR_COLLECTION_SHADER_H
