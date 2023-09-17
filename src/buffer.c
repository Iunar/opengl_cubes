#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "buffer.h"

Buffer create_buffer(GLenum type, bool dynamic) {
    Buffer buf = {
        .type = type,
        .dynamic = dynamic,
    };

    glGenBuffers(1, &buf.handle);
    return buf;
}

void bind_buffer(Buffer buffer) {
    glBindBuffer(buffer.type, buffer.handle);
}
void unbind_buffer(Buffer buffer) {
    glBindBuffer(buffer.type, 0);
}

void fill_buffer(Buffer buffer, size_t byte_size, void* data, GLenum type) {

    if(!buffer.dynamic) {
        glBufferData(buffer.type, byte_size, data, GL_STATIC_DRAW);
    } else {
        glBufferData(buffer.type, byte_size, data, GL_DYNAMIC_DRAW);
    }
}

void destroy_buffer(Buffer buffer) {
    unbind_buffer(buffer);
    glDeleteBuffers(1, &buffer.handle);
}
