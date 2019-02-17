#include "textureCubemap.h"

void TextureCubemap::bind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, handle);
}

void
TextureCubemap::texImage(GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format,
                         GLenum type, const GLvoid *data)
{
    bind();

    for (unsigned int i = 0; i < 6; i++)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, internalFormat, width, height, border, format, type,
                     NULL);
    }
}

void TextureCubemap::texParameteri(GLenum name, GLint value)
{
    bind();
    glTexParameteri(GL_TEXTURE_CUBE_MAP, name, value);
}


