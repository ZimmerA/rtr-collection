#include "frameBuffer.h"

void FrameBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, handle);
}

void FrameBuffer::attachTexture2D(GLenum attachment, GLuint texture, const Texture &tex, GLint level)
{
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, tex.handle, level);
}
