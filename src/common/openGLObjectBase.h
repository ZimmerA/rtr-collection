#ifndef RTR_COLLECTION_OPENGLOBJECTBASE_H
#define RTR_COLLECTION_OPENGLOBJECTBASE_H
#include <glad/glad.h>
#include <algorithm>
template<typename T>
class OpenGLObjectBase {
public:
    OpenGLObjectBase(): handle(T::create()) {}
    ~OpenGLObjectBase(){T::destroy(handle);}

    OpenGLObjectBase(const OpenGLObjectBase &) = delete;
    OpenGLObjectBase &operator=(const OpenGLObjectBase &) = delete;
    OpenGLObjectBase(OpenGLObjectBase &&other): handle(other.handle) { other.handle = 0; }
    OpenGLObjectBase &operator=(OpenGLObjectBase &&other) { if (this != &other) { T::destroy(handle); std::swap(handle, other.handle);}}
    typename T::value_type handle;
};


#endif //RTR_COLLECTION_OPENGLOBJECTBASE_H
