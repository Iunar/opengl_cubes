#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdbool.h>

struct buffer {
    GLuint handle;
    GLenum type;
    bool dynamic;
};
typedef struct buffer Buffer;

Buffer create_buffer(GLenum type, bool dynamic);
void fill_buffer(Buffer buffer, size_t byte_size, void* data, GLenum type);
void destroy_buffer(Buffer buffer);
void bind_buffer(Buffer buffer);
void unbind_buffer(Buffer buffer);

#endif // BUFFER_H
