#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "buffer.h"

struct VAO {
    GLuint handle;
};
typedef struct VAO VAO;

VAO create_vao();
void bind_vao(VAO vao);
void set_vertex_attribute(size_t index, size_t element_count,
        GLenum data_type, GLboolean normalized, GLsizei stride, GLvoid* offset);
void delete_vao(VAO vao);

#endif // VAO_H
