#ifndef RTR_COLLECTION_TEXTURE_H
#define RTR_COLLECTION_TEXTURE_H

#include <glad/glad.h>
#include "openGLObjectBase.h"

struct TextureTraits {
    typedef GLuint value_type;

    static value_type create();

    static void destroy(value_type handle);
};

class Texture : public OpenGLObjectBase<TextureTraits> {
public:
    Texture(GLenum target);

    void bind();

    void texImage();

    void texParameteri(GLenum name, GLint value);

private:
    GLenum target;
};


#endif //RTR_COLLECTION_TEXTURE_H
