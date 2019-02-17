#ifndef RTR_COLLECTION_FRAMEBUFFER_H
#define RTR_COLLECTION_FRAMEBUFFER_H

#include "glad/glad.h"
#include "glTraits.h"
#include "openGLObjectBase.h"
#include "texture.h"

class FrameBuffer : public OpenGLObjectBase<FrameBufferTraits> {
public:
    void bind();

    void attachTexture2D(GLenum attachment, GLuint texture, const Texture &tex, GLint level);
};

#endif //RTR_COLLECTION_FRAMEBUFFER_H
