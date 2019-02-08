#ifndef RTR_COLLECTION_SHADER_H
#define RTR_COLLECTION_SHADER_H

#define ATTRIBUTE_POSITION 0
#define ATTRIBUTE_TEXCOORD 1
#define ATTRIBUTE_NORMAL 2
#define ATTRIBUTE_TANGENT 3
#define ATTRIBUTE_BITANGENT 4

#include "glad/glad.h"
#include "openGLObjectBase.h"

// TODO: Find a way to use SFINAE to deal with the shadertype in the  OpenGLObjectBase constructor
/*
struct ShaderTraits {
    typedef GLuint value_type;
    typedef GLenum parameter_type;
    static value_type Create(parameter_type shaderType);
    static void Destroy(value_type handle);
};
*/

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

struct ShaderProgramTraits {
    typedef GLuint value_type;

    static value_type create();

    static void destroy(value_type handle);
};

class ShaderProgram : public OpenGLObjectBase<ShaderProgramTraits> {
public:
    void attachShader(Shader *shader);

    void linkProgram();

    void use();
};

#endif //RTR_COLLECTION_SHADER_H
