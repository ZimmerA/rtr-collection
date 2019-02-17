#ifndef RTR_COLLECTION_GLTRAITS_H
#define RTR_COLLECTION_GLTRAITS_H

#include "glad/glad.h"

// TODO: Find a way to use SFINAE to deal with the shadertype in the  OpenGLObjectBase constructor
/*
struct ShaderTraits {
    typedef GLuint value_type;
    typedef GLenum parameter_type;
    static value_type Create(parameter_type shaderType);
    static void Destroy(value_type handle);
};
*/

struct ShaderProgramTraits {
    typedef GLuint value_type;

    static value_type create();

    static void destroy(value_type handle);
};

struct TextureTraits {
    typedef GLuint value_type;

    static value_type create();

    static void destroy(value_type handle);
};

struct VertexArrayObjectTraits {
    typedef GLuint value_type;

    static value_type create();

    static void destroy(value_type handle);
};

struct VertexBufferObjectTraits {
    typedef GLuint value_type;

    static value_type create();

    static void destroy(value_type handle);
};

struct FrameBufferTraits {
    typedef GLuint value_type;

    static value_type create();

    static void destroy(value_type handle);
};

#endif //RTR_COLLECTION_GLTRAITS_H
