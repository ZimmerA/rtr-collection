#include "texture.h"

void Texture::bind()
{
    glBindTexture(target, handle);
}

void Texture::texImage2D(GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format,
                         GLenum type, const GLvoid *data)
{
    bind();
    glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);
    glGenerateMipmap(target);
}

void Texture::texParameteri(GLenum name, GLint value)
{
    bind();
    glTexParameteri(target, name, value);
}
