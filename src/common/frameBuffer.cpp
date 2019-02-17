#include "frameBuffer.h"

void FrameBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, handle);
}

void FrameBuffer::attachTexture(GLenum attachment, GLuint textureTarget, GLuint textureHandle, GLint level)
{
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, textureTarget, textureHandle, level);
}
