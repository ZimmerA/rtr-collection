#include "texture.h"

TextureTraits::value_type TextureTraits::create()
{
    value_type handle;
    glGenTextures(1, &handle);
    return handle;
}

void TextureTraits::destroy(TextureTraits::value_type handle)
{
    glDeleteTextures(1,&handle);
}

Texture::Texture(GLenum target) : target(target)
{

}

void Texture::bind()
{
    glBindTexture(target, handle);
}

void Texture::texParameteri(GLenum name, GLint value)
{
    bind();
    glTexParameteri(target, name, value);
}

void Texture::texImage()
{

}
