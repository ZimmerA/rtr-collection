#include "frameBuffer.h"

FrameBufferTraits::value_type FrameBufferTraits::create()
{
    value_type handle;
    glGenFramebuffers(1, &handle);
    return handle;
}

void FrameBufferTraits::destroy(FrameBufferTraits::value_type handle)
{
    glDeleteFramebuffers(1, &handle);
}

void FrameBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, handle);
}

void FrameBuffer::attachTexture2D(GLenum attachment, GLuint texture, const Texture &tex, GLint level)
{
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, tex.handle, level);
}
