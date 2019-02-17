#ifndef RTR_COLLECTION_TEXTURECUBEMAP_H
#define RTR_COLLECTION_TEXTURECUBEMAP_H

#include "glad/glad.h"
#include "glTraits.h"
#include "openGLObjectBase.h"

class TextureCubemap : public OpenGLObjectBase<TextureTraits> {
public:
    void bind();

    void texImage(GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border,
                  GLenum format,
                  GLenum type, const GLvoid *data);

    void texParameteri(GLenum name, GLint value);
};

#endif //RTR_COLLECTION_TEXTURECUBEMAP_H
