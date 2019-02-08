#ifndef RTR_COLLECTION_FRAMEBUFFER_H
#define RTR_COLLECTION_FRAMEBUFFER_H

#include "glad/glad.h"
#include "openGLObjectBase.h"
#include "texture.h"

struct FrameBufferTraits {
    typedef GLuint value_type;

    static value_type create();

    static void destroy(value_type handle);
};

class FrameBuffer : public OpenGLObjectBase<FrameBufferTraits> {
public:
    void bind();

    void attachTexture2D(GLenum attachment, GLuint texture, const Texture &tex, GLint level);
};

#endif //RTR_COLLECTION_FRAMEBUFFER_H
