#include "texture.h"

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, handle);
}

void Texture::texImage(GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border,
                       GLenum format,
                       GLenum type, const GLvoid *data)
{
    bind();
    glTexImage2D(GL_TEXTURE_2D, level, internalFormat, width, height, border, format, type, data);
}

void Texture::texParameteri(GLenum name, GLint value)
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, name, value);
}
