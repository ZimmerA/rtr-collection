#ifndef RTR_COLLECTION_TEXTURE_H
#define RTR_COLLECTION_TEXTURE_H

#include "glad/glad.h"
#include "openGLObjectBase.h"
#include "glTraits.h"

class Texture : public OpenGLObjectBase<TextureTraits> {
public:
    void bind();

    void texImage(GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border,
                  GLenum format,
                  GLenum type, const GLvoid *data);

    void texParameteri(GLenum name, GLint value);
};


#endif //RTR_COLLECTION_TEXTURE_H
